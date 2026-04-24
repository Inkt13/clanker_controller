#include <Arduino.h>
#include <Robot.h>
#include <SerialDecoder.h>

void setup()
{
  Serial.begin(115200);

  robot.initDisplay();
  // robot.displayStartupScreen();

  pinMode(ARM_MOTOR_IN1_PIN, OUTPUT);
  pinMode(ARM_MOTOR_IN2_PIN, OUTPUT);
  pinMode(ARM_MOTOR_IN3_PIN, OUTPUT);
  pinMode(ARM_MOTOR_IN4_PIN, OUTPUT);

  pinMode(ARM_MOTOR_DOWN_SENSOR_PIN, INPUT);
  pinMode(ARM_MOTOR_UP_SENSOR_PIN,   INPUT);
  
  pinMode(CLAW_SERVO_PIN, OUTPUT);

  robot.initClaw();
  robot.setClawServoAngle(20);
  // delay(2000);
  // robot.displayTaskCode("123+123");
  robot.setArmMotorPosition(1000);
  
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
  // robot.updateScroll();
}