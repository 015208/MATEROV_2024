#include <servoSys.h>

servoMovement::servoMovement(const uint8_t servoPins, const uint16_t INPUT_MIN, const uint16_t INPUT_MAX, const uint16_t MIN_ANGLE, const uint16_t MAX_ANGLE)
    : m_servoPins(servoPins), m_INPUT_MIN(INPUT_MIN), m_INPUT_MAX(INPUT_MAX), m_MIN_ANGLE(MIN_ANGLE), m_MAX_ANGLE(MAX_ANGLE)
{
}

void servoMovement::servoAttach()
{
    attach(m_servoPins, 500, 2500); // attach pin to init
}

void servoMovement::mapWriteServoControl(uint16_t readValue)
{
    writeServoAngle = map(readValue, m_INPUT_MIN, m_INPUT_MAX, m_MIN_ANGLE, m_MAX_ANGLE); // servo map to potentiometer
    writeMicroseconds(writeServoAngle);                                                   // write the angle to the servo
}

void servoMovement::writeMicrosecondsServoControl(uint16_t PULSE)
{
    pulse = PULSE;
    writeMicroseconds(pulse); // write the pulse to servo
}