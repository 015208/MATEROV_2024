#include <movement.h>

float turnSpeed = 0;

void Movement::mecaunumMovement(int16_t MappedValue_X, int16_t MappedValue_Y, int16_t MappedValue_Turn, int16_t UPDOWN_AXIS) // movement control of mecannum
{
  theta = atan2(MappedValue_Y, MappedValue_X);
  power = hypot(MappedValue_X, MappedValue_Y);

  sinAngle = sin(theta - (PI / 4));
  cosAngle = cos(theta - (PI / 4));
  max = max(abs(sinAngle), abs(cosAngle));

  FL_Speed = power * cosAngle / max - MappedValue_Turn;
  FR_Speed = power * sinAngle / max + MappedValue_Turn;
  BL_Speed = power * sinAngle / max - MappedValue_Turn;
  BR_Speed = power * cosAngle / max + MappedValue_Turn;

  UFL_Speed = UPDOWN_AXIS;
  UFR_Speed = UPDOWN_AXIS;
  UBL_Speed = UPDOWN_AXIS;
  UBR_Speed = UPDOWN_AXIS;
}
void Movement::showDirection(int16_t Turn) // reveal the direction of motor
{
  if ((power + abs(Turn)) > 1)
  { // Show DIR
    dir[0] /= power + abs(Turn);
    dir[1] /= power + abs(Turn);
    dir[2] /= power + abs(Turn);
    dir[3] /= power + abs(Turn);
  }
}