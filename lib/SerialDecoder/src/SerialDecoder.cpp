#include <SerialDecoder.h>

namespace SerialDecoder {
    void handleSerialData(byte b) {
        switch (static_cast<Command>(b)) {
            case Command::SetArmMotorPositionDown:
                robot.setArmMotorPosition(ARM_MOTOR_POSITION_DOWN);
                break;
            case Command::SetArmMotorPositionUp:
                robot.setArmMotorPosition(ARM_MOTOR_POSITION_UP);
                break;
            case Command::OpenClaw:
                robot.openClaw();
                break;
            case Command::CloseClaw:
                robot.closeClaw();
                break;
            default:
                Serial.write("Unknown data detected\n");
        }
    }
}