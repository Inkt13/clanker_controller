#pragma once
#include <Robot.h>
// This file contains helpers that handle byte level serial data from the Raspberry Pi 5

namespace SerialDecoder {
    enum class Command {
        SetArmMotorPositionUp   = 0x11,
        SetArmMotorPositionDown = 0x12,
        OpenClaw                = 0x21,       
        CloseClaw               = 0x22,
    };

    void handleSerialData(byte b);
}