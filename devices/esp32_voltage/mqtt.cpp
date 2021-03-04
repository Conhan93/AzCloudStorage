#include "mqtt.h"


MQTT::MQTT() {}
bool MQTT::initMQTT(char * connection_string)
{
  return Esp32MQTTClient_Init((const uint8_t *) connection_string);
}
void MQTT::AddProperty( char* key, char* value)
{
    Esp32MQTTClient_Event_AddProp(
        message,
        key,
        value
        );
}
void MQTT::GenerateMessage(char* payload)
{
    message = Esp32MQTTClient_Event_Generate(payload, MESSAGE);
}
void MQTT::send_message(char* payload)
{

  if(Esp32MQTTClient_SendEvent(payload)) 
  {
    Serial.print("Payload sent: ");
    Serial.println(payload);  
  }
  else
    Serial.println("failed to send message");
}
void MQTT::send_message()
{
    if(Esp32MQTTClient_SendEventInstance(message)) 
  {
    Serial.println("Payload event sent");  
  }
  else
    Serial.println("failed to send message");
}
