#include <Arduino.h>
#include <Robot.h>


void setup() {
  // put your setup code here, to run once:
  
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  Serial.write("AAAAAAAAAAAAAAAAAAA \n");
}