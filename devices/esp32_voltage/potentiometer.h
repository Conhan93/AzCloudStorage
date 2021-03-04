#ifndef VOLT_SENSOR_INCLUDED
#define VOLT_SENSOR_INCLUDED

#include "Arduino.h"

typedef float Volt; // unit for volt
/**
 * @brief Class to handle measuring
 *  volts from a potentiometer
 */
class Potentiometer
{
    private:
    // stored values
    uint8_t potpin; // ADC pin for potentiometer
    Volt voltage; // voltage on circuit
    float maxPotValue; // max readable value on pin

    public:
        /**
         * @brief construct potentiometer object
         * 
         * @param potpin ADC pin, default value 36
         * @param voltage voltage on circuit, default 3.3 for esp32
         * @param maxpotvalue max readable value on pin, default
         *  4095
         */
        Potentiometer(uint8_t potpin = 36, Volt voltage = 3.3 ,
                    float maxPotValue = 4095);

        /**
         * @brief reads from analog pin and converts value to Volt.
         * 
         * @return returns analog input converted into Volt(float)
         */
        Volt GetVoltValue();

};

#endif