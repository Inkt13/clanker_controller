#include <SerialDecoder.h>

namespace SerialDecoder
{
    static int bytesNeeded = 0;
    static int value = 0;
    static Command currentCommand; // 🔥 NEW

    static char displayText[32] = {0}; // Buffer for task code text
    static int displayTextLength = 0;

    void handleSerialData(byte b)
    {
        // 🔥 Receiving bytes
        if (bytesNeeded > 0)
        {
            value = (value << 8) | b;
            bytesNeeded--;

            // Handle multi-byte text reception
            if (currentCommand == Command::SetDisplayText)
            {
                if (b == 0 || displayTextLength >= 31) // Null terminator or max length
                {
                    displayText[displayTextLength] = '\0';
                    bytesNeeded = 0;
                    Serial.print("Display text received: ");
                    Serial.println(displayText);
                    robot.displayTaskCode(getDisplayText());
                }
                else
                {
                    displayText[displayTextLength++] = b;
                }
                return;
            }

            if (bytesNeeded == 0)
            {
                Serial.print("Value received: ");
                Serial.println(value);

                // 🔥 Decide based on command
                switch (currentCommand)
                {
                case Command::SetArmMotorPositionValue:
                    robot.setArmMotorPosition(value);
                    break;

                case Command::SetClawAngleValue:
                    robot.setClawServoAngle(value);
                    break;

                default:
                    break;
                }
            }
            return;
        }

        // 🔥 New command comes here
        switch (static_cast<Command>(b))
        {
        default:
            Serial.print("Unknown byte: ");
            Serial.println(b, HEX);
            break;

        case Command::ResetArmMotorPosition:
            robot.resetArmMotorPosition();
            break;

        case Command::SetArmMotorPositionDown:
            robot.setArmMotorPosition(ARM_MOTOR_POSITION_DOWN);
            break;

        case Command::SetArmMotorPositionUp:
            robot.setArmMotorPosition(ARM_MOTOR_POSITION_UP);
            break;

        case Command::SetArmMotorPositionValue:
            Serial.println("Receiving arm position...");
            currentCommand = Command::SetArmMotorPositionValue;
            value = 0;
            bytesNeeded = 2;
            break;

        case Command::SetClawAngleValue:
            Serial.println("Receiving claw angle...");
            currentCommand = Command::SetClawAngleValue;
            value = 0;
            bytesNeeded = 1;
            break;

        case Command::OpenClaw:
            robot.openClaw();
            break;

        case Command::CloseClaw:
            robot.closeClaw();
            break;

        case Command::SetDisplayText:
            Serial.println("Receiving display text...");
            currentCommand = Command::SetDisplayText;
            displayTextLength = 0;
            bytesNeeded = 255; // Max length, will be terminated by null byte or limit
            break;
        }
    }

    const char *getDisplayText()
    {
        return displayText;
    }
}