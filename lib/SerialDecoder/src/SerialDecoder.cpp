#include <SerialDecoder.h>

SerialDecoder::handleSerialData(byte b) {
    switch (b) {
        case Command::SetArmMotorPositionDown:
            robot.setArmMotorPosition(ARM_MOTOR_POSITION_DOWN);
        case Command::SetArmMotorPositionUp:
            robot.setArmMotorPosition(ARM_MOTOR_POSITION_UP);
        case Command::OpenClaw:
            robot.openClaw();
        case Command::CloseClaw:
            robot.closeClaw();
    }
}