#pragma once

#include <Arduino.h>

class digitalData
{
private:
    uint8_t m_D_Pin1;
    uint8_t m_mode;
    uint8_t prevData;
    uint8_t realTimeData1, readTimeData2;

public:
    digitalData(const uint8_t D_PIN1, const uint8_t mode); // mode = INPUT_PULLUP / INPUT
    bool getDigitalData();
};