#pragma once

#include <Arduino.h>

class analogData
{
private:
    const uint8_t m_pin;
    int16_t MappedValue;

public:
    analogData(const uint8_t pin);
    uint16_t get_rawAnalogValue() { return analogRead(m_pin); };
    int16_t mapValue(const int16_t JY_MIN_VALUE, const int16_t JY_MAX_VALUE, const int16_t WHEEL_MIN_SPEED, const int16_t WHEEL_MAX_SPEED,
                      const int16_t MIN_DEADZONE, const int16_t MAX_DEADZONE);
    int16_t getMappedValue() { return MappedValue; };
};