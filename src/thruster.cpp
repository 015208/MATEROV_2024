#include <thruster.h>

Thruster::Thruster(const uint8_t pin_thruster_in,
                   const unsigned long MAX_THRUSTER_SPEED, const unsigned long STOP_THRUSTER_SPEED,
                   const unsigned long MIN_THRUSTER_SPEED, const int8_t thrusterDirMode)
    : m_pin_thruster_in(pin_thruster_in),
      m_MAX_THRUSTER_SPEED(MAX_THRUSTER_SPEED), m_STOP_THRUSTER_SPEED(STOP_THRUSTER_SPEED),
      m_MIN_THRUSTER_SPEED(MIN_THRUSTER_SPEED), m_thrusterDirMode(thrusterDirMode)
{
  pinMode(m_pin_thruster_in, OUTPUT);
}

void Thruster::thrusterAttach() // IMPORTANT INIT FORMAT FOR THRUSTERS
{
  attach(m_pin_thruster_in);
}

void Thruster::thrustSetSpeed(int16_t thruster_speed)
{
  m_thruster_speed = constrain(thruster_speed, MIN_SPEED, MAX_SPEED);
  if (m_thrusterDirMode == 1)
  {
    if (m_thruster_speed > 0)
      m_thruster_speed = map(m_thruster_speed, STOP_SPEED, MAX_SPEED, m_STOP_THRUSTER_SPEED, m_MAX_THRUSTER_SPEED);
    else if (m_thruster_speed < 0)
      m_thruster_speed = map(m_thruster_speed, STOP_SPEED, MIN_SPEED, m_STOP_THRUSTER_SPEED, m_MIN_THRUSTER_SPEED);
    else if (m_thruster_speed == 0)
      m_thruster_speed = map(m_thruster_speed, STOP_SPEED, STOP_SPEED, m_STOP_THRUSTER_SPEED, m_STOP_THRUSTER_SPEED);
  }
  if (m_thrusterDirMode == -1)
  {
    if (m_thruster_speed > 0)
      m_thruster_speed = map(m_thruster_speed, STOP_SPEED, MAX_SPEED, m_STOP_THRUSTER_SPEED, m_MIN_THRUSTER_SPEED);
    else if (m_thruster_speed < 0)
      m_thruster_speed = map(m_thruster_speed, STOP_SPEED, MIN_SPEED, m_STOP_THRUSTER_SPEED, m_MAX_THRUSTER_SPEED);
    else if (m_thruster_speed == 0)
      m_thruster_speed = map(m_thruster_speed, STOP_SPEED, STOP_SPEED, m_STOP_THRUSTER_SPEED, m_STOP_THRUSTER_SPEED);
  }
  writeMicroseconds(m_thruster_speed);
}
