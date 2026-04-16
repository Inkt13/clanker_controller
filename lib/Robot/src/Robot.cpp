#include <Arduino.h>
#include "Robot.h"

Robot robot;

Robot::Robot()
{
    armMotorCurrentPosition = 0;
    armMotorTargetPosition = 0;
}

void Robot::initClaw()
{
    clawServo.attach(CLAW_SERVO_PIN);
}

void Robot::setClawServoAngle(int angle)
{
    clawServo.write(angle);
}

void Robot::stepArmMotorUp()
{
    armMotorCurrentPosition++;
    if (armMotorCurrentPosition > ARM_MOTOR_POSITION_MAX)
        armMotorCurrentPosition = ARM_MOTOR_POSITION_MAX;

    const int armMotorPins[] = {ARM_MOTOR_IN4_PIN, ARM_MOTOR_IN3_PIN, ARM_MOTOR_IN2_PIN, ARM_MOTOR_IN1_PIN};
    const int numPins = 4;
    for (int i = 0; i < numPins; i++)
    {
        if (i != 0)
            digitalWrite(armMotorPins[i - 1], LOW);
        digitalWrite(armMotorPins[i], HIGH);
        delayMicroseconds(ARM_MOTOR_STEP_DELAY_US);
    }
    digitalWrite(armMotorPins[3], LOW);
}

void Robot::stepArmMotorDown()
{
    armMotorCurrentPosition--;
    if (armMotorCurrentPosition < ARM_MOTOR_POSITION_MIN)
        armMotorCurrentPosition = ARM_MOTOR_POSITION_MIN;
    const int armMotorPins[] = {ARM_MOTOR_IN1_PIN, ARM_MOTOR_IN2_PIN, ARM_MOTOR_IN3_PIN, ARM_MOTOR_IN4_PIN};
    const int numPins = 4;
    for (int i = 0; i < numPins; i++)
    {
        if (i != 0)
            digitalWrite(armMotorPins[i - 1], LOW);
        digitalWrite(armMotorPins[i], HIGH);
        delayMicroseconds(ARM_MOTOR_STEP_DELAY_US);
    }
    digitalWrite(armMotorPins[3], LOW);
}

void Robot::resetArmMotorPosition()
{
    armMotorCurrentPosition = 0;
    armMotorTargetPosition = 0;

    for (int i = 0; i < ARM_MOTOR_POSITION_MAX; i++)
    {
        stepArmMotorDown();
    }
}

void Robot::setArmMotorPosition(int position)
{
    if (position > ARM_MOTOR_POSITION_MAX)
        position = ARM_MOTOR_POSITION_MAX;

    if (position < ARM_MOTOR_POSITION_MIN)
        position = ARM_MOTOR_POSITION_MIN;

    armMotorTargetPosition = position;
}

void Robot::openClaw()
{
    setClawServoAngle(CLAW_SERVO_OPEN_ANGLE);
}

void Robot::closeClaw()
{
    setClawServoAngle(CLAW_SERVO_CLOSE_ANGLE);
}

void Robot::updateArmMotor()
{
    if (armMotorCurrentPosition > armMotorTargetPosition)
    {
        stepArmMotorDown();
    }
    if (armMotorCurrentPosition < armMotorTargetPosition)
    {
        stepArmMotorUp();
    }
}
