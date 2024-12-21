#include <analog.h>

analogData::analogData(const uint8_t pin)
    : m_pin(pin)
{
  pinMode(m_pin, INPUT); // set pin to INPUT
}

int16_t analogData::mapValue(const int16_t JY_MIN_VALUE, const int16_t JY_MAX_VALUE,
                              const int16_t WHEEL_MIN_SPEED, const int16_t WHEEL_MAX_SPEED, const int16_t MIN_DEADZONE, const int16_t MAX_DEADZONE)
{
  if (analogRead(m_pin) >= MIN_DEADZONE && analogRead(m_pin) <= MAX_DEADZONE)
    MappedValue = 0;
  else
    MappedValue = map(analogRead(m_pin), JY_MIN_VALUE, JY_MAX_VALUE, WHEEL_MIN_SPEED, WHEEL_MAX_SPEED);
  return MappedValue;
}