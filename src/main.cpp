#include <Arduino.h>
#include <Robot.h>
#include <SerialDecoder.h>

void setup() {
  Serial.begin(115200);
  robot.initClaw();
}

// byte data sent from the Raspberry PI 5
byte serialData = 0;

void loop() {
  if (Serial.available() > 0) {
    serialData = Serial.read();
    SerialDecoder::handleSerialData(serialData);
  }
  robot.updateArmMotor();
}