#pragma once
#include <Arduino.h>

class Movement
{
private:
  double theta, power;
  double sinAngle, cosAngle, max;

  int16_t FL_Speed, FR_Speed, BL_Speed, BR_Speed;
  int16_t UFL_Speed, UFR_Speed, UBL_Speed, UBR_Speed;
  int dir[4];

public:
  void mecaunumMovement(int16_t MappedValue_X, int16_t MappedValue_Y, int16_t MappedValue_Turn, int16_t UPDOWN_AXIS);
  void showDirection(int16_t MappedValue_Turn);

  int16_t get_speed_FL() { return FL_Speed; }
  int16_t get_speed_FR() { return FR_Speed; }
  int16_t get_speed_BL() { return BL_Speed; }
  int16_t get_speed_BR() { return BR_Speed; }

  int16_t get_speed_UFL() { return UFL_Speed; }
  int16_t get_speed_UFR() { return UFR_Speed; }
  int16_t get_speed_UBL() { return UBL_Speed; }
  int16_t get_speed_UBR() { return UBR_Speed; }
};