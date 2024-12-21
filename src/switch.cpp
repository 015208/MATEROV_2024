#include <switch.h>

Switch::Switch(const uint8_t pin1, const uint8_t pin2, uint8_t mode)
    : m_pin1(pin1), m_pin2(pin2), m_mode(mode)
{
    pinMode(m_pin1, mode);
    pinMode(m_pin2, mode);
}

bool Switch::getDigitalData1()
{
    state1 = digitalRead(m_pin1);
    return state1;
}
bool Switch::getDigitalData2()
{
    state2 = digitalRead(m_pin2);
    return state2;
}

uint8_t Switch::getTwoStateData()
{
    getDigitalData1();
    getDigitalData2();
    if (state1 == 0 && state2 == 1)
        return 0;
    if (state1 == 1 && state2 == 1)
        return 1;
    if (state1 == 1 && state2 == 0)
        return 2;
    return 3;
}