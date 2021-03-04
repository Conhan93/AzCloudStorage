#include "potentiometer.h"



Potentiometer::Potentiometer(uint8_t potpin ,Volt voltage ,float maxPotValue)
{
    this->potpin = potpin;
    this->voltage = voltage;
    this->maxPotValue = maxPotValue;
}

Volt Potentiometer::GetVoltValue()
{
    return (analogRead(potpin) * (voltage/maxPotValue));
}