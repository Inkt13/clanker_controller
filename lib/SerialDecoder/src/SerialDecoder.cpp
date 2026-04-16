#include <SerialDecoder.h>

namespace SerialDecoder
{
    static int bytesNeeded = 0;
    static int value = 0;
    void handleSerialData(byte b)
    {

        if (bytesNeeded > 0)
        {
            value = (value << 8) | b;
            bytesNeeded--;

            if (bytesNeeded == 0)
            {
                Serial.print("Target position: ");
                Serial.println(value);

                robot.setArmMotorPosition(value);
            }
            return;
        }
        switch (static_cast<Command>(b))
        {
        default:
            Serial.print("Unknown byte: ");
            Serial.println(b, HEX);
            break;
        case Command::ResetArmMotorPosition:
            Serial.println("Resetting Arm Position");
            robot.resetArmMotorPosition();
            break;
        case Command::SetArmMotorPositionDown:
            Serial.println("Going down");
            robot.setArmMotorPosition(ARM_MOTOR_POSITION_DOWN);
            break;
        case Command::SetArmMotorPositionUp:
            Serial.println("Going up");
            robot.setArmMotorPosition(ARM_MOTOR_POSITION_UP);
            break;

        case Command::SetArmMotorPositionValue:
            Serial.println("Receiving position...");
            value = 0;

            bytesNeeded = 2;
            break;

        case Command::OpenClaw:
            Serial.println("Opening Claw");
            robot.openClaw();
            break;
        case Command::CloseClaw:
            Serial.println("Closing Claw");
            robot.closeClaw();
            break;
        }
    }
}