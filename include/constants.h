#pragma once
#include <Arduino.h>

#define SERIAL_BAUD_RATE 115200
#define ThrusterInitMS 250

#define JY_MIN_VALUE 0
#define JY_MAX_VALUE 1023
constexpr byte PIN_JOYSTICK_X = A6;
constexpr byte PIN_JOYSTICK_Y = A7;
constexpr byte PIN_JOYSTICK_TURN = A11;
constexpr byte PIN_JOYSTICK_UPDOWN = A12;
constexpr byte PIN_BUTTON_1 = 52;
constexpr byte PIN_BUTTON_2 = 50;
constexpr byte PIN_BUTTON_3 = 51;
constexpr byte PIN_BUTTON_4 = 53;
constexpr byte PIN_BUTTON_5 = 5;
constexpr byte PIN_BUTTON_6 = 4;
constexpr byte PIN_BUTTON_7 = 3;
constexpr byte PIN_BUTTON_8 = 2;

constexpr byte PIN_SWITCH_1 = 13; // 22
constexpr byte PIN1_SWITCH_1 = 12;
constexpr byte PIN_SWITCH_2 = 11; // 23
constexpr byte PIN1_SWITCH_2 = 10;
constexpr byte PIN_SWITCH_3 = 9; // 24
constexpr byte PIN1_SWITCH_3 = 8;
constexpr byte PIN_SWITCH_4 = 7; // 25
constexpr byte PIN1_SWITCH_4 = 6;

#define ANALOG_MIN_VALUE 0
#define ANALOG_MAX_VALUE 1023
constexpr byte PIN_SLIDER_1 = A4;
constexpr byte PIN_SLIDER_2 = A5;
constexpr byte PIN_SLIDER_3 = A8;
constexpr byte PIN_SLIDER_4 = A13;
constexpr byte PIN_SLIDER_5 = A10;
constexpr byte PIN_SLIDER_6 = A9;
constexpr byte PIN_POT_1 = A0;
constexpr byte PIN_POT_2 = A1;
const byte PIN_LEFT_CLAW = 27;     // 39 //4
const byte PIN_RIGHT_CLAW = 26;    // 2 //8
const byte PIN_FRONT_BUCKET = 24;  // 39 //4
const byte PIN_BACK_BUCKET = 25;   // 2 //8
const byte PIN_INF_SPIN_CLAW = 28; // 38
const uint16_t MIN_PULSE_SERVO = 1000;
const uint16_t NO_PULSE_SERVO = 1500;
const uint16_t MAX_PULSE_SERVO = 2000;
const uint16_t LEFT_CLAW_CLOSE_ANGLE = 997;     // 44
const uint16_t LEFT_CLAW_OPEN_ANGLE = 1678;     // 110
const uint16_t RIGHT_CLAW_CLOSE_ANGLE = 1832;   // 125
const uint16_t RIGHT_CLAW_OPEN_ANGLE = 1162;    // 60
const uint16_t FRONT_BUCKET_CLOSE_ANGLE = 1255; // 69
const uint16_t FRONT_BUCKET_OPEN_ANGLE = 1884;  // 130
const uint16_t BACK_BUCKET_CLOSE_ANGLE = 1719;  // 114
const uint16_t BACK_BUCKET_OPEN_ANGLE = 1080;   // 52

constexpr int16_t PWM_MIN_SPEED = -255;
constexpr byte PWM_MAX_SPEED = 255;
constexpr byte PWM_NO_SPEED = 0;

constexpr byte NORMAL_FACTOR = 1;
constexpr float MIDDLE_FACTOR = 0.7;
constexpr float MECANNUM_LOWER_FACTOR = 0.3;
constexpr float TURNING_LOWER_FACTOR = 0.9;
constexpr float UPDOWN_LOWER_FACTOR = 0.35;

constexpr byte PIN_FL_THRUSTER = 22;  // BRIAN'S:  22 BLACK_8_BLACK    ISAAC'S:12
constexpr byte PIN_UFL_THRUSTER = 35; //          35 PURPLE_7_WHITE          10
constexpr byte PIN_FR_THRUSTER = 32;  //          32 YELLLOW_4_WHITE        39
constexpr byte PIN_UFR_THRUSTER = 30; //         30 BROWN_2_WHITE          5
constexpr byte PIN_BL_THRUSTER = 34;  //          34  BLUE_6_WHITE           13
constexpr byte PIN_UBL_THRUSTER = 33; //          33 GREEN_5_WHITE           9
constexpr byte PIN_BR_THRUSTER = 29;  //          29 BLACK_1_WHITE          2
constexpr byte PIN_UBR_THRUSTER = 31; //         31 RED_3_WHITE            6

constexpr uint16_t THRUSTER_STOP_SPEED = 1480; // long wires, causing a pwm signal offset
constexpr uint16_t THRUSTER_MAX_SPEED = 2000;
constexpr uint16_t THRUSTER_MIN_SPEED = 1000;

uint16_t MECANNUM_THRUSTER_NOLIMIT_MAX_SPEED = 2000;
uint16_t MECANNUM_THRUSTER_NOLIMIT_MIN_SPEED = 1000;

uint16_t TOP_THRUSTER_NOLIMIT_MAX_SPEED = 2000;
uint16_t TOP_THRUSTER_NOLIMIT_MIN_SPEED = 1000;

constexpr int DIR_FORWARD = 1, DIR_BACKWARD = -1;
