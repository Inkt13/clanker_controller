import serial
import time

ser = serial.Serial('COM9', 115200, timeout=0.1)
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




OpenClaw()






# read response
time.sleep(0.03)  # give Arduino time to respond
response = ser.read_all()

if response:
    print("Arduino says:", response)
else:
    print("...silence... 👻")

ser.close()

