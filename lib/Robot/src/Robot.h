#pragma once
#include <ESP32Servo.h>
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// The ESP32 microcontroller is responsible for controlling two components in the robot:
// The robotic arm motor that moves along the y axis (via FSK30J + L298N driver) and the claw (via MG90S micro servo)

// Pin number configuration for an ESP32 dev module.
// Adjust these pin numbers if your wiring differs.
#define CLAW_SERVO_PIN 25

// Wiring notes:
// These IN1, IN2, IN3 and IN4 are labeled on the L298N motor driver
// OUT1, 2, 3, 4 on the L298N are connected to the Green, Red, Black and Blue wire on the FSK30J motor
#define ARM_MOTOR_IN1_PIN 26
#define ARM_MOTOR_IN2_PIN 27
#define ARM_MOTOR_IN3_PIN 14
#define ARM_MOTOR_IN4_PIN 12

// Arm motor sensors
#define ARM_MOTOR_UP_SENSOR_PIN 35
#define ARM_MOTOR_DOWN_SENSOR_PIN 34

// OLED Display pins
#define OLED_MOSI 23
#define OLED_CLK 18
#define OLED_DC 17
#define OLED_CS 5
#define OLED_RESET 16

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define CLAW_SERVO_OPEN_ANGLE 20
#define CLAW_SERVO_CLOSE_ANGLE 175

#define ARM_MOTOR_POSITION_MAX 1315
#define ARM_MOTOR_POSITION_MIN 0
#define ARM_MOTOR_POSITION_UP 1200
#define ARM_MOTOR_POSITION_DOWN 100
#define ARM_MOTOR_STEP_DELAY_US 650

class Robot
{
    Servo clawServo;
    int armMotorCurrentPosition;
    int armMotorTargetPosition;
    Adafruit_SSD1306 display;
    
    int scrollPosition;
    unsigned long lastScrollTime;
    char currentTaskCode[256];
    bool isDisplayingTaskCode;

    void stepArmMotorUp();
    void stepArmMotorDown();
    bool armMotorUpSensorDetected();
    bool armMotorDownSensorDetected();
public:
    Robot();
    void updateScroll();
    void resetArmMotorPosition();
    void setArmMotorPosition(int position);
    void setClawServoAngle(int angle);

    void SetArmMotorPositionValue(int position);

    void initClaw();
    void openClaw();
    void closeClaw();

    void updateArmMotor();
    
    void initDisplay();
    void displayTaskCode(const char* text);
    void displayStartupScreen();
    void displayScrollingText(const char* text, int x, int y, int textSize);
};

extern Robot robot;
