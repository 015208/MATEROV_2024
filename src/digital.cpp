#include <digital.h>


int buttonPressed = 0;
digitalData::digitalData(const uint8_t D_PIN1, const uint8_t mode)
    : m_D_Pin1(D_PIN1),m_mode(mode)
{
    pinMode(m_D_Pin1, mode); //set pin to either INPUT/INPUT_PULLUP
}

bool digitalData::getDigitalData()
{
    realTimeData1 = digitalRead(m_D_Pin1); //digitalRead 1 OR 0
    // prevData = realTimeData;
    return realTimeData1;
}