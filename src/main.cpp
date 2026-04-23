#include <Arduino.h>
#include <Robot.h>
#include <SerialDecoder.h>

void setup()
{
  Serial.begin(115200);

  robot.initDisplay();
  robot.displayStartupScreen();

  pinMode(ARM_MOTOR_IN1_PIN, OUTPUT);
  pinMode(ARM_MOTOR_IN2_PIN, OUTPUT);
  pinMode(ARM_MOTOR_IN3_PIN, OUTPUT);
  pinMode(ARM_MOTOR_IN4_PIN, OUTPUT);

  robot.initClaw();
}

// byte data sent from the Raspberry PI 5
byte serialData = 0;

void loop()
{
  if (Serial.available() > 0)
  {
    serialData = Serial.read();
    SerialDecoder::handleSerialData(serialData);
  }
  robot.updateArmMotor();
  robot.updateScroll();
  robot.displayStartupScreen();
}