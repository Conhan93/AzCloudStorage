#ifndef DEVICE_INCLUDED
#define DEVICE_INCLUDED

// wifi
#include <WiFi.h>
// mqtt
#include "MQTT.h"
#include "lightsensor.h"

#include "Arduino.h"
#include <ArduinoJson.h>
/**
 * @brief Class to handle device functions.
 */
class Device
{
    private:
        MQTT* Azureconnection;
        LightSensor* sensor;

        // stored values
        Luminosity threshold; // Luminosity difference
        Luminosity prevlum, curlum;

        char payload[128];
        char ID[6]; // Device ID

        
        void GenerateID(); // generates device id from MAC address
        void GetReadings(); // gets values from sensor
        void UpdateValues(); // updates stored measurement values
        void CreatePayload(); // formats payload with device values
        void SendPayload(); // sends device payload using Azureconnector

        /**
         *  @brief checks if luminosity readings difference
         *      exceeds threshold
         * 
         *  @return returns true if difference is over threshold
         *      amount, false if not.
         */
        bool IsOverThreshold();

        /**
         *  @brief Initializes ESP WiFi
         * 
         *  @param SSID WiFi SSID
         *  @param pass WiFi password
         */
        void InitWiFi(char* SSID, char* pass);
    public:

        /**
         *  @brief constructs Device object with default values
         * 
         *  @param pot_pin pin for LightSensor device, is set to 36 by default
         *  @param threshold the difference in Luminosity
         *      to reach before sending new messages, 20% by default
         */
        Device(uint8_t pot_pin = 36, Luminosity threshold = 10);
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