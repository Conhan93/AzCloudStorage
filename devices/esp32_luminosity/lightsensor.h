#ifndef LIGHT_SENSOR_INCLUDED
#define LIGHT_SENSOR_INCLUDED

#include "Arduino.h"

typedef float Volt; // unit for volt
typedef float Luminosity;
/**
 * @brief Class to handle measuring
 *  volts from a LightSensor
 */
class LightSensor
{
    private:
    // stored values
    uint8_t potpin; // ADC pin for LightSensor
    float maxPotValue; // max readable value on pin

    public:
        /**
         * @brief construct LightSensor object
         * 
         * @param potpin ADC pin, default value 36
         * @param maxpotvalue max readable value on pin, default
         *  4095
         */
        LightSensor(uint8_t potpin = 36, float maxPotValue = 4095);

        /**
         * @brief reads from analog pin and converts value to relative
         *  Luminosity(% of max value).
         * 
         * @return returns analog input converted into Volt(float)
         */
        Luminosity GetLuminosityValue();

};

#endif