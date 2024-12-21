#include <Arduino.h>
#include <thruster.h>
#include <movement.h>
#include <digital.h>
#include <analog.h>
#include <constants.h>
#include <servoSys.h>
#include <interface.h>
#include <switch.h>

Interface lcd(20, 4, true);
void InitThruster();
void lcdPrint();

float speedValueX, speedValueY, speedValueTurn, speedValueUPDOWN;

bool SERIAL_EN = false;
uint8_t lastState;

Thruster thrusterFL(PIN_FL_THRUSTER, MECANNUM_THRUSTER_NOLIMIT_MAX_SPEED, THRUSTER_STOP_SPEED, MECANNUM_THRUSTER_NOLIMIT_MIN_SPEED, DIR_FORWARD);
Thruster thrusterFR(PIN_FR_THRUSTER, MECANNUM_THRUSTER_NOLIMIT_MAX_SPEED, THRUSTER_STOP_SPEED, MECANNUM_THRUSTER_NOLIMIT_MIN_SPEED, DIR_BACKWARD);
Thruster thrusterBL(PIN_BL_THRUSTER, MECANNUM_THRUSTER_NOLIMIT_MAX_SPEED, THRUSTER_STOP_SPEED, MECANNUM_THRUSTER_NOLIMIT_MIN_SPEED, DIR_FORWARD);
Thruster thrusterBR(PIN_BR_THRUSTER, MECANNUM_THRUSTER_NOLIMIT_MAX_SPEED, THRUSTER_STOP_SPEED, MECANNUM_THRUSTER_NOLIMIT_MIN_SPEED, DIR_BACKWARD);

Thruster thrusterTFL(PIN_UFL_THRUSTER, TOP_THRUSTER_NOLIMIT_MAX_SPEED, THRUSTER_STOP_SPEED, TOP_THRUSTER_NOLIMIT_MIN_SPEED, DIR_BACKWARD);
Thruster thrusterTFR(PIN_UFR_THRUSTER, TOP_THRUSTER_NOLIMIT_MAX_SPEED, THRUSTER_STOP_SPEED, TOP_THRUSTER_NOLIMIT_MIN_SPEED, DIR_FORWARD);
Thruster thrusterTBL(PIN_UBL_THRUSTER, TOP_THRUSTER_NOLIMIT_MAX_SPEED, THRUSTER_STOP_SPEED, TOP_THRUSTER_NOLIMIT_MIN_SPEED, DIR_FORWARD);
Thruster thrusterTBR(PIN_UBR_THRUSTER, TOP_THRUSTER_NOLIMIT_MAX_SPEED, THRUSTER_STOP_SPEED, TOP_THRUSTER_NOLIMIT_MIN_SPEED, DIR_BACKWARD);

Movement mecannum;

analogData JOYSTICK_X_AXIS(PIN_JOYSTICK_X);
analogData JOYSTICK_Y_AXIS(PIN_JOYSTICK_Y);
analogData JOYSTICK_Turn(PIN_JOYSTICK_TURN);
analogData JOYSTICK_UPDOWN(PIN_JOYSTICK_UPDOWN);
analogData SLIDER_1(PIN_SLIDER_1);
analogData ControlClawServo_SLIDER(PIN_SLIDER_2);
analogData SLIDER_3(PIN_SLIDER_3);
analogData STONE_CLAMP_SLIDER(PIN_SLIDER_4);
analogData SLIDER_5(PIN_SLIDER_5);
analogData SLIDER_6(PIN_SLIDER_6);
analogData POTENTIOMETER_1(PIN_POT_1);
analogData POTENTIOMETER_2(PIN_POT_2);

servoMovement LEFT_CLAW(PIN_LEFT_CLAW, ANALOG_MIN_VALUE, ANALOG_MAX_VALUE, LEFT_CLAW_CLOSE_ANGLE, LEFT_CLAW_OPEN_ANGLE);
servoMovement RIGHT_CLAW(PIN_RIGHT_CLAW, ANALOG_MIN_VALUE, ANALOG_MAX_VALUE, RIGHT_CLAW_CLOSE_ANGLE, RIGHT_CLAW_OPEN_ANGLE);
servoMovement FRONT_BUCKET(PIN_FRONT_BUCKET, ANALOG_MIN_VALUE, ANALOG_MAX_VALUE, FRONT_BUCKET_CLOSE_ANGLE, FRONT_BUCKET_OPEN_ANGLE);
servoMovement BACK_BUCKET(PIN_BACK_BUCKET, ANALOG_MIN_VALUE, ANALOG_MAX_VALUE, BACK_BUCKET_CLOSE_ANGLE, BACK_BUCKET_OPEN_ANGLE);
servoMovement INF_SPIN_CLAW(PIN_INF_SPIN_CLAW, 0, 0, 0, 0);

digitalData stateButton1(PIN_BUTTON_1, INPUT_PULLUP);
digitalData stateButton2(PIN_BUTTON_2, INPUT_PULLUP);
digitalData stateButton3(PIN_BUTTON_3, INPUT_PULLUP);
digitalData stateButton4(PIN_BUTTON_4, INPUT_PULLUP);
digitalData stateButton5(PIN_BUTTON_5, INPUT_PULLUP);
digitalData stateButton6(PIN_BUTTON_6, INPUT_PULLUP);
digitalData stateButton7(PIN_BUTTON_7, INPUT_PULLUP);
digitalData stateButton8(PIN_BUTTON_8, INPUT_PULLUP);

Switch stateSwitch1(PIN_SWITCH_1, PIN1_SWITCH_1, INPUT_PULLUP);
Switch stateSwitch2(PIN_SWITCH_2, PIN1_SWITCH_2, INPUT_PULLUP);
Switch stateSwitch3(PIN_SWITCH_3, PIN1_SWITCH_3, INPUT_PULLUP);
Switch stateSwitch4(PIN_SWITCH_4, PIN1_SWITCH_4, INPUT_PULLUP);

void setup()
{

  if (SERIAL_EN)
    Serial.begin(SERIAL_BAUD_RATE);
  lcd.init();
  lcd.setCursor(5, 2);
  lcd.print("initing....");
  thrusterFL.thrusterAttach();
  thrusterFR.thrusterAttach();
  thrusterBL.thrusterAttach();
  thrusterBR.thrusterAttach();
  thrusterTFL.thrusterAttach();
  thrusterTFR.thrusterAttach();
  thrusterTBL.thrusterAttach();
  thrusterTBR.thrusterAttach();
  InitThruster();
  LEFT_CLAW.servoAttach();
  RIGHT_CLAW.servoAttach();
  lcd.clear();
  lastState = stateSwitch1.getTwoStateData();
}

void loop()
{
  
  speedValueX = JOYSTICK_X_AXIS.mapValue(JY_MAX_VALUE, JY_MIN_VALUE, PWM_MIN_SPEED, PWM_MAX_SPEED, 485, 500);
  speedValueY = JOYSTICK_Y_AXIS.mapValue(JY_MIN_VALUE, JY_MAX_VALUE, PWM_MIN_SPEED, PWM_MAX_SPEED, 475, 500);
  speedValueTurn = JOYSTICK_Turn.mapValue(JY_MAX_VALUE, JY_MIN_VALUE, PWM_MIN_SPEED, PWM_MAX_SPEED, 460, 480);
  speedValueUPDOWN = JOYSTICK_UPDOWN.mapValue(JY_MAX_VALUE, JY_MIN_VALUE, PWM_MIN_SPEED, PWM_MAX_SPEED, 480, 510);

  if (stateSwitch3.getTwoStateData() == 0)
  {
    speedValueX *= MECANNUM_LOWER_FACTOR;
    speedValueY *= MECANNUM_LOWER_FACTOR;
    speedValueTurn *= MECANNUM_LOWER_FACTOR;
    speedValueUPDOWN *= NORMAL_FACTOR;
  }
  else if (stateSwitch3.getTwoStateData() == 1)
  {
    speedValueX *= MIDDLE_FACTOR;
    speedValueY *= MIDDLE_FACTOR;
    speedValueTurn *= MIDDLE_FACTOR;
    speedValueUPDOWN *= MIDDLE_FACTOR;
  }
  else
  {
    speedValueX *= NORMAL_FACTOR;
    speedValueY *= NORMAL_FACTOR;
    speedValueTurn *= TURNING_LOWER_FACTOR;
    speedValueUPDOWN *= UPDOWN_LOWER_FACTOR;
  }

  mecannum.mecaunumMovement(speedValueX, speedValueY, speedValueTurn, speedValueUPDOWN);

  thrusterFL.thrustSetSpeed(mecannum.get_speed_FL());
  thrusterFR.thrustSetSpeed(mecannum.get_speed_FR());
  thrusterBL.thrustSetSpeed(mecannum.get_speed_BL());
  thrusterBR.thrustSetSpeed(mecannum.get_speed_BR());

  thrusterTFL.thrustSetSpeed(mecannum.get_speed_UFL());
  thrusterTFR.thrustSetSpeed(mecannum.get_speed_UFR());
  thrusterTBL.thrustSetSpeed(mecannum.get_speed_UBL());
  thrusterTBR.thrustSetSpeed(mecannum.get_speed_UBR());

  LEFT_CLAW.mapWriteServoControl(ControlClawServo_SLIDER.get_rawAnalogValue());
  RIGHT_CLAW.mapWriteServoControl(ControlClawServo_SLIDER.get_rawAnalogValue());
  // FRONT_BUCKET.mapWriteServoControl(STONE_CLAMP_SLIDER.get_rawAnalogValue());
  // BACK_BUCKET.mapWriteServoControl(STONE_CLAMP_SLIDER.get_rawAnalogValue());

  if (stateButton7.getDigitalData() == LOW && stateButton8.getDigitalData() == HIGH)
  {
    INF_SPIN_CLAW.writeMicrosecondsServoControl(MIN_PULSE_SERVO); // anti-clockwise
  }
  else if (stateButton8.getDigitalData() == LOW && stateButton7.getDigitalData() == HIGH)
  {
    INF_SPIN_CLAW.writeMicrosecondsServoControl(MAX_PULSE_SERVO); // clockwise
  }
  else
  {
    INF_SPIN_CLAW.writeMicrosecondsServoControl(NO_PULSE_SERVO);
  }
  lcdPrint();
  Serial.println();
}

void InitThruster()
{
  thrusterFL.writeMicroseconds(THRUSTER_STOP_SPEED);
  thrusterFR.writeMicroseconds(THRUSTER_STOP_SPEED);
  thrusterBL.writeMicroseconds(THRUSTER_STOP_SPEED);
  thrusterBR.writeMicroseconds(THRUSTER_STOP_SPEED);
  thrusterTFL.writeMicroseconds(THRUSTER_STOP_SPEED);
  thrusterTFR.writeMicroseconds(THRUSTER_STOP_SPEED);
  thrusterTBL.writeMicroseconds(THRUSTER_STOP_SPEED);
  thrusterTBR.writeMicroseconds(THRUSTER_STOP_SPEED);
  delay(ThrusterInitMS);
  thrusterFL.writeMicroseconds(THRUSTER_MAX_SPEED);
  thrusterFR.writeMicroseconds(THRUSTER_MAX_SPEED);
  thrusterBL.writeMicroseconds(THRUSTER_MAX_SPEED);
  thrusterBR.writeMicroseconds(THRUSTER_MAX_SPEED);
  thrusterTFL.writeMicroseconds(THRUSTER_MAX_SPEED);
  thrusterTFR.writeMicroseconds(THRUSTER_MAX_SPEED);
  thrusterTBL.writeMicroseconds(THRUSTER_MAX_SPEED);
  thrusterTBR.writeMicroseconds(THRUSTER_MAX_SPEED);
  delay(ThrusterInitMS);
  thrusterFL.writeMicroseconds(THRUSTER_STOP_SPEED);
  thrusterFR.writeMicroseconds(THRUSTER_STOP_SPEED);
  thrusterBL.writeMicroseconds(THRUSTER_STOP_SPEED);
  thrusterBR.writeMicroseconds(THRUSTER_STOP_SPEED);
  thrusterTFL.writeMicroseconds(THRUSTER_STOP_SPEED);
  thrusterTFR.writeMicroseconds(THRUSTER_STOP_SPEED);
  thrusterTBL.writeMicroseconds(THRUSTER_STOP_SPEED);
  thrusterTBR.writeMicroseconds(THRUSTER_STOP_SPEED);
  delay(ThrusterInitMS);
}

void lcdPrint()
{
  if (stateSwitch1.getTwoStateData() == 0 || stateSwitch1.getTwoStateData() == 1)
  {

    if (stateSwitch1.getTwoStateData() != lastState)
    {
      lcd.clear();
      lastState = stateSwitch1.getTwoStateData();
    }
    if (stateSwitch1.getTwoStateData() == lastState)
    {

      lcd.setCursor(0, 0);
      lcd.print(thrusterFL.thrusterGetSpeed());
      lcd.setCursor(5, 0);
      lcd.print(thrusterFR.thrusterGetSpeed());
      lcd.setCursor(10, 0);
      lcd.print(thrusterBL.thrusterGetSpeed());
      lcd.setCursor(15, 0);
      lcd.print(thrusterBR.thrusterGetSpeed());
      lcd.setCursor(0, 1);
      lcd.print(thrusterTFL.thrusterGetSpeed());
      lcd.setCursor(5, 1);
      lcd.print(thrusterTFR.thrusterGetSpeed());
      lcd.setCursor(10, 1);
      lcd.print(thrusterTBL.thrusterGetSpeed());
      lcd.setCursor(15, 1);
      lcd.print(thrusterTBR.thrusterGetSpeed());

      lcd.setCursor(0, 2);
      lcd.print(JOYSTICK_X_AXIS.get_rawAnalogValue());
      lcd.setCursor(5, 2);
      lcd.print(JOYSTICK_Y_AXIS.get_rawAnalogValue());
      lcd.setCursor(0, 3);
      lcd.print(JOYSTICK_Turn.get_rawAnalogValue());
      lcd.setCursor(5, 3);
      lcd.print(JOYSTICK_UPDOWN.get_rawAnalogValue());
      if (stateSwitch3.getTwoStateData() == 0)
      {
        lcd.setCursor(12, 3);
        lcd.print("  UPDOWN");
      }
      else if (stateSwitch3.getTwoStateData() == 1)
      {
        {
          lcd.setCursor(12, 3);
          lcd.print("  MIDDLE");
        }
      }
      else
      {
        lcd.setCursor(12, 3);
        lcd.print("MECANNUM");
      }
    }
  }
  else if (stateSwitch1.getTwoStateData() == 2)
  {
    if (stateSwitch1.getTwoStateData() != lastState)
    {
      lcd.clear();
      lastState = stateSwitch1.getTwoStateData();
    }
    lcd.setCursor(0, 0);
    lcd.print(stateSwitch1.getTwoStateData());
    lcd.setCursor(1, 0);
    lcd.print(stateSwitch2.getTwoStateData());
    lcd.setCursor(2, 0);
    lcd.print(stateSwitch3.getTwoStateData());
    lcd.setCursor(3, 0);
    lcd.print(stateSwitch4.getTwoStateData());

    lcd.setCursor(9, 0);
    lcd.print(stateButton1.getDigitalData());
    lcd.setCursor(10, 0);
    lcd.print(stateButton2.getDigitalData());
    lcd.setCursor(11, 0);
    lcd.print(stateButton3.getDigitalData());
    lcd.setCursor(12, 0);
    lcd.print(stateButton4.getDigitalData());
    lcd.setCursor(13, 0);
    lcd.print(stateButton5.getDigitalData());
    lcd.setCursor(14, 0);
    lcd.print(stateButton6.getDigitalData());
    lcd.setCursor(15, 0);
    lcd.print(stateButton7.getDigitalData());
    lcd.setCursor(16, 0);
    lcd.print(stateButton8.getDigitalData());

    lcd.setCursor(0, 1);
    lcd.print(SLIDER_1.get_rawAnalogValue());
    lcd.print("  ");
    lcd.setCursor(5, 1);
    lcd.print(ControlClawServo_SLIDER.get_rawAnalogValue());
    lcd.print("  ");
    lcd.setCursor(10, 1);
    lcd.print(SLIDER_3.get_rawAnalogValue());
    lcd.print("  ");
    lcd.setCursor(15, 1);
    lcd.print(STONE_CLAMP_SLIDER.get_rawAnalogValue());
    lcd.print("  ");
    lcd.setCursor(10, 2);
    lcd.print(SLIDER_5.get_rawAnalogValue());
    lcd.print("  ");
    lcd.setCursor(15, 2);
    lcd.print(SLIDER_6.get_rawAnalogValue());
    lcd.print("  ");

    lcd.setCursor(0, 2);
    lcd.print(POTENTIOMETER_1.get_rawAnalogValue());
    lcd.print("  ");
    lcd.setCursor(5, 2);
    lcd.print(POTENTIOMETER_2.get_rawAnalogValue());
    lcd.print("  ");

    lcd.setCursor(0, 3);
    lcd.print(LEFT_CLAW.getWriteAngle());
    lcd.print(" ");
    lcd.setCursor(5, 3);
    lcd.print(RIGHT_CLAW.getWriteAngle());
    lcd.print(" ");
    lcd.setCursor(10, 3);
    lcd.print(INF_SPIN_CLAW.getINF_SPINAngle());
  }
}