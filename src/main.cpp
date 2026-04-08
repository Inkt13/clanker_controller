#include <Arduino.h>
#include <Servo.h>

Servo servo270;

int myFunction(int, int);

int servo_270_angle(int angle)
{
  return (int) (angle * 180.0 / 270.0);
}
void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  servo270.attach(3);
}

void loop() {
  servo270.write(servo_270_angle(180));
  delay(5000);
  servo270.write(0);
  delay(5000);
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}