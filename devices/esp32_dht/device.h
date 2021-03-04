#ifndef DEVICE_INCLUDED
#define DEVICE_INCLUDED

// wifi
#include <WiFi.h>
// mqtt
#include "MQTT.h"

#include "Arduino.h"
#include "DHT.h"
#include <ArduinoJson.h>

class Device
{
    private:
        DHT* sensor;
        MQTT* Azureconnection;

        // stored values
        float threshold; // temperature difference
        float curtemperature, prevtemperature;
        float curhumidity, prevhumidity;

        char payload[128];
        char ID[6]; // Device ID

        
        void GenerateID(); // generates device id from MAC address
        void GetReadings(); // gets values from DHT
        void UpdateValues(); // updates stored measurement values
        void CreatePayload(); // formats payload with device values
        void SendPayload(); // sends device payload using Azureconnector

        /**
         *  @brief checks if temperature readings difference
         *      exceeds threshold
         * 
         *  @return returns true if difference is over threshold
         *      amount, false if not.
         */
        bool IsOverThreshold();

        /**
         *  @brief Initalizes ESP WiFi
         * 
         *  @param SSID WiFi SSID
         *  @param pass WiFi password
         */
        void InitWiFi(char* SSID, char* pass);
    public:

        /**
         *  @brief constructs Device object with default values
         * 
         *  @param dht_pin pin for dht11 device, is set to 2 by default
         *  @param threshold the difference in temperature
         *      to reach before sending new messages, 0.5 by default
         */
        Device(uint8_t dht_pin = 2, float threshold = 0.5);
        ~Device(); // destructor

        /**
         * @brief Initializes Device and device components 
         * 
         * @param connectionstring IoTHub device connectionstring
         * @param SSID WiFi SSID
         * @param pass Wifi Password
         * 
         */
        void InitDevice(char* connectionstring, char* SSID, char* pass);

        // runs device
        void run();
};


#endif