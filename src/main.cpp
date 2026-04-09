#include <Arduino.h>
#include <Robot.h>
#include <SerialDecoder.h>

void setup() {
  Serial.begin(9600);
  robot.setArmMotorPosition(ARM_MOTOR_POSITION_MAX);
}

// byte data sent from the Raspberry PI 5
byte serialData = 0;

void loop() {
  serialData = Serial.read();
  SerialDecoder::handleSerialData(serialData);
  robot.updateArmMotor();
}