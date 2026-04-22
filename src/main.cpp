#include <Arduino.h>
#include <Robot.h>
#include <SerialDecoder.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_MOSI 11
#define OLED_CLK 13
#define OLED_DC 2
#define OLED_CS 10
#define OLED_RESET 8

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, OLED_DC, OLED_RESET, OLED_CS);

void setup()
{
  Serial.begin(115200);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }

  // Clear the buffer
  display.clearDisplay();

  // Display Text
  display.setTextSize(1);              // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);             // Start at top-left corner
  display.println(F("Arduino Nano"));
  display.println(F("OLED Test..."));

  display.setTextSize(2); // Draw larger text
  display.setCursor(0, 30);
  display.println(F("SUCCESS!"));

  display.display(); // Actually push the data to the screen

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
}