#pragma once
#include <Arduino.h>
#include <Servo.h>

class servoMovement : public Servo
{

private:
    const uint8_t m_servoPins;
    uint16_t readValuePOTData;
    uint16_t writeServoAngle;
    uint16_t pulse;
    const uint16_t m_INPUT_MIN, m_INPUT_MAX, m_MIN_ANGLE, m_MAX_ANGLE;

public:
    servoMovement(const uint8_t servoPins, const uint16_t INPUT_MIN, const uint16_t INPUT_MAX, const uint16_t MIN_ANGLE, const uint16_t MAX_ANGLE);
    void servoAttach();
    void mapWriteServoControl(uint16_t readValue);
    void writeMicrosecondsServoControl(uint16_t PULSE);

    uint16_t getWriteAngle() { return writeServoAngle; };
    uint16_t getINF_SPINAngle() { return pulse; };
};