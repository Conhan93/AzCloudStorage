#ifndef IOT_HUB_INCLUDED
#define IOT_HUB_INCLUDED

#include "Arduino.h"
#include <Esp32MQTTClient.h>

/**
 *  @brief Class to handle MQTT communications
 */
class MQTT
{
  private:
    // MQTT message instance
    EVENT_INSTANCE* message;
  public:
    // default constructor
    MQTT();
    /**
     * @brief sends MQTT message event instance
     *   Use GenerateMessage() to create event instance
     *   to send.
     * 
     */
    void send_message();
    /**
     * @brief sends MQTT message with @p payload
     * 
     *  @param payload message string
     */
    void send_message(char* payload);
    /**
     * @brief establishes connection with broker
     * 
     * @param connection_string your IoTHub device
     *  connection string
     * @return returns true if succesfully connected,
     *  false if not.
     */
    bool initMQTT(char* connection_string);
    /**
     * @brief Adds property to MQTT message event instance,
     * 
     * @param key key for property
     * @param value value for property
     */
    void AddProperty(char* key, char* value);
    /**
     * @brief Generates message event, stored in class instance
     * 
     * @param payload payload string to be added
     *  to generated message event
     */
    void GenerateMessage(char* payload);
};

#endif
