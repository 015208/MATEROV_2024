#include <Arduino.h>
#include <Servo.h>

class Thruster : public Servo
{
private:
  const uint8_t m_pin_thruster_in;
  const unsigned long m_MAX_THRUSTER_SPEED;
  const unsigned long m_STOP_THRUSTER_SPEED;
  const unsigned long m_MIN_THRUSTER_SPEED;
  int8_t m_thrusterDirMode;
  const uint8_t MAX_SPEED = 255;
  const int16_t MIN_SPEED = -255;
  const uint8_t STOP_SPEED = 0;
  uint16_t LIMITED_SPEED;

protected:
  int16_t m_thruster_speed = 0;

public:
  Thruster(const uint8_t pin_thruster_in,
           const unsigned long MAX_THRUSTER_SPEED, const unsigned long STOP_THRUSTER_SPEED,
           const unsigned long MIN_THRUSTER_SPEED, const int8_t thrusterDir_mode);

  void thrustSetSpeed(int16_t thruster_speed);
  void thrusterAttach();
  int16_t thrusterGetSpeed() const { return m_thruster_speed; };
};