#include <Arduino.h>
#include <Robot.h>
#include <SerialDecoder.h>

void setup() {
  // Not sure if i have to do this but im not taking any chances lol
  robot = Robot();
  Serial.begin(9600);
}

// byte data sent from the Raspberry PI 5
byte serialData = 0;

void loop() {
  serialData = Serial.read();
  SerialDecoder::handleSerialData(serialData);
  robot.updateArmMotor();
}