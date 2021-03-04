#include "lightsensor.h"



LightSensor::LightSensor(uint8_t potpin ,float maxPotValue)
{
    this->potpin = potpin;
    this->maxPotValue = maxPotValue;
}

Luminosity LightSensor::GetLuminosityValue()
{
    return (((float)analogRead(potpin)/maxPotValue) * 100);
}