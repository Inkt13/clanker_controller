import serial
import time

ser = serial.Serial('COM3', 115200, timeout=0.1)
time.sleep(2)  # Arduino reset moment

def ResetArmMotorPosition():
    ser.write(bytes([0x10]))

def SetArmMotorPositionValue(pos):

    high = (pos>> 8) & 0xFF;
    low = pos & 0xFF;

    ser.write(bytes([0x30, high, low]))
    
def OpenClaw():
    ser.write(bytes([0x21]))

def CloseClaw():
    ser.write(bytes([0x22]))

def SetClawAngle(angle):
    ser.write(bytes([0x40, angle]))

def SetDisplayText(text):
    """Send task code text to display (e.g., '123+321' or '213+132')"""
    ser.write(bytes([0x50]))  # Command byte for SetDisplayText
    # Send each character followed by null terminator
    for char in text:
        ser.write(bytes([ord(char)]))
    ser.write(bytes([0]))  # Null terminator


# Example: Send a scrambled task code to the display
SetDisplayText("213+132")







# read response
time.sleep(0.03)  # give Arduino time to respond
response = ser.read_all()

if response:
    print("Arduino says:", response)
else:
    print("...silence... 👻")

ser.close()

