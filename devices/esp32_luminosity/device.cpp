#include "device.h"
#include "float.h"
#include "time.h"
#include "stdlib.h"
#include <array>

Device::Device(uint8_t pot_pin, Luminosity threshold)
{
    // create objects
    sensor = new LightSensor(pot_pin);
    Azureconnection = new MQTT();

    // init values
    this->threshold = threshold;
    prevlum = FLT_MIN;
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
    curlum = sensor->GetLuminosityValue();
}
void Device::GenerateID()
{
    std::array<uint8_t, 10> address;
    WiFi.macAddress(address.begin());
    int seed = 0;

    for(auto digit : address)
        seed += (int)(digit);

    srand(seed+1);
    itoa((rand() % 9999) + 1,ID,10);
}
bool Device::IsOverThreshold()
{
    return (abs(curlum - prevlum) > threshold);
}
void Device::UpdateValues()
{
    prevlum = curlum;
}
void Device::CreatePayload()
{
    DynamicJsonDocument doc(1024);
    doc["ID"] = /*WiFi.macAddress();*/ ID;
    doc["luminosity"] = curlum;
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
    Azureconnection->AddProperty("type","luminosity");

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
