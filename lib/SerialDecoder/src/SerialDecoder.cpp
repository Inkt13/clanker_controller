#include <SerialDecoder.h>

namespace SerialDecoder {
    void handleSerialData(byte b) {
        switch (static_cast<Command>(b)) {
            default:
                Serial.print("Unknown byte: ");
                Serial.println(b, HEX);
                break;
            case Command::ResetArmMotorPosition:
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
            case Command::OpenClaw:
                robot.openClaw();
                break;
            case Command::CloseClaw:
                robot.closeClaw();
                break;
        }
    }
}