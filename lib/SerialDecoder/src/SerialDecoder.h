#pragma once
#include <Robot.h>
// This file contains helpers that handle byte level serial data from the Raspberry Pi 5

namespace SerialDecoder
{
    enum class Command
    {
        ResetArmMotorPosition = 0x10,
        SetArmMotorPositionUp = 0x11,
        SetArmMotorPositionDown = 0x12,

        SetArmMotorPositionValue = 0x30,

        OpenClaw = 0x21,
        CloseClaw = 0x22,

        SetClawAngleValue = 0x40
    };

    void handleSerialData(byte b);
}