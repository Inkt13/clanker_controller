#include <Arduino.h>
#include "Robot.h"

Robot::Robot()
{
    clawServo.attach(CLAW_SERVO_PIN);
    setClawServoAngle(0);

    resetArmMotorPosition();
}

void Robot::setClawServoAngle(int angle)
{
    clawServo.write(angle);
}


void Robot::stepArmMotorUp()
{
    const int armMotorPins[] = {ARM_MOTOR_IN1_PIN,ARM_MOTOR_IN2_PIN,ARM_MOTOR_IN3_PIN,ARM_MOTOR_IN4_PIN};
    const int numPins = 4;
    for(int i = 0;i < numPins;i++)
    {
        digitalWrite(armMotorPins[i],HIGH);
        if(i == 0)continue;
        digitalWrite(armMotorPins[i-1], LOW);
        delayMicroseconds(ARM_MOTOR_STEP_DELAY_US);
    }
    digitalWrite(armMotorPins[3],LOW);
}

void Robot::stepArmMotorDown()
{
    const int armMotorPins[] = {ARM_MOTOR_IN4_PIN,ARM_MOTOR_IN3_PIN,ARM_MOTOR_IN2_PIN,ARM_MOTOR_IN1_PIN};
    const int numPins = 4;
    for(int i = 0;i < numPins;i++)
    {
        digitalWrite(armMotorPins[i],HIGH);
        if(i == 0)continue;
        digitalWrite(armMotorPins[i-1], LOW);
        delayMicroseconds(ARM_MOTOR_STEP_DELAY_US);
    }
    digitalWrite(armMotorPins[3],LOW);
}

void Robot::resetArmMotorPosition()
{
    armMotorCurrentPosition = 0;
    armMotorTargetPosition = 0;

    for(int i = 0;i <= ARM_MOTOR_POSITION_MAX;i++)
    {
        stepArmMotorDown();
    }
}

void Robot::setArmMotorPosition(int position)
{
    armMotorTargetPosition = position;
}

void Robot::openClaw()
{
    setClawServoAngle(180);
}

void Robot::closeClaw()
{
    setClawServoAngle(0);
}

void Robot::updateArmMotor()
{
    if(armMotorCurrentPosition > armMotorTargetPosition)
    {
        stepArmMotorDown();
    }
    if(armMotorCurrentPosition < armMotorTargetPosition)
    {
        stepArmMotorUp();
    }
}