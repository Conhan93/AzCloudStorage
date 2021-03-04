#include "device.h"
#include "float.h"
#include "time.h"
#include "stdlib.h"
#include <array>

Device::Device(uint8_t dht_pin, float threshold)
{
    // create objects
    sensor = new DHT(dht_pin, DHT11);
    Azureconnection = new MQTT();

    // init values
    this->threshold = threshold;
    prevhumidity = FLT_MIN;
    prevtemperature = FLT_MIN;
}
Device::~Device()
{
  // destroy related objects
  delete sensor;
  delete Azureconnection;
}
void Device::InitDevice(char* connectionstring, char* SSID, char* pass)
{
    InitWiFi(SSID, pass);
    Azureconnection->initMQTT(connectionstring);
    sensor->begin();

    configTime(3600,3600,"pool.ntp.org");

    GenerateID();
}
void Device::InitWiFi(char* SSID, char* pass)
{
    WiFi.begin(SSID,pass);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
}
void Device::GetReadings()
{
    curtemperature = sensor->readTemperature();
    curhumidity = sensor->readHumidity();
}
void Device::GenerateID()
{
    std::array<uint8_t, 10> address;
    WiFi.macAddress(address.begin());
    int seed = 0;

    for(auto digit : address)
        seed += (int)(digit);

    srand(seed);
    itoa((rand() % 9999) + 1,ID,10);
}
bool Device::IsOverThreshold()
{
    return (abs(curtemperature - prevtemperature) > threshold);
}
void Device::UpdateValues()
{
    prevhumidity = curhumidity;
    prevtemperature = curtemperature;
}
void Device::CreatePayload()
{
    DynamicJsonDocument doc(1024);
    doc["ID"] = /*WiFi.macAddress();*/ ID;
    doc["temperature"] = curtemperature;
    doc["humidity"] = curhumidity;
    doc["messageCreated"] = time(NULL);
    serializeJson(doc, payload);
}
void Device::SendPayload()
{
    // create message
    Azureconnection->GenerateMessage(payload);

    // add properties
    Azureconnection->AddProperty("name","Conny");
    Azureconnection->AddProperty("school", "Nackademin");
    Azureconnection->AddProperty("type","dht");

    // uncomment payload to send only payload string
    Azureconnection->send_message(/*payload*/);
}
void Device::run()
{
    GetReadings();

    // abort if condition not met
    if(!IsOverThreshold()) return;

    UpdateValues();
    CreatePayload();
    SendPayload();

}
