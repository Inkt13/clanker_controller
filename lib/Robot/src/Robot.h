#pragma once
#include <Servo.h>
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// The Arduino Nano microcontroller is responsible for controlling two components in the robot:
// The robotic arm motor that moves along the y axis (via FSK30J + L298N driver) and the claw (via MG90S micro servo)

// Pin number configuration. This is set according to the wiring as of 04/09/2026
// That being said yeah there's nothing wired for the claw, so I set it to 2 for now
#define CLAW_SERVO_PIN 3

// OLED Display pins
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_MOSI 11
#define OLED_CLK 13
#define OLED_DC 2
#define OLED_CS 10
#define OLED_RESET 8

// Wiring notes:
// These IN1, IN2, IN3 and IN4 are labeled on the L289N motor driver
// OUT1, 2, 3, 4 on the L289N are  connected to the Green, Red, Black and Blue wire on the FSK30J motor
#define ARM_MOTOR_IN1_PIN 7
#define ARM_MOTOR_IN2_PIN 6
#define ARM_MOTOR_IN3_PIN 5
#define ARM_MOTOR_IN4_PIN 4

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

    void stepArmMotorUp();
    void stepArmMotorDown();

public:
    Robot();
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
};

extern Robot robot;
