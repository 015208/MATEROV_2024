#pragma once
#include <Arduino.h>

class Switch
{
private:
    bool state1, state2;
    // uint8_t state;
    const uint8_t m_pin1, m_pin2, m_mode;

public:
    Switch(const uint8_t pin1, const uint8_t pin2, uint8_t mode);

    uint8_t getTwoStateData();
    bool getDigitalData1();
    bool getDigitalData2();
};
