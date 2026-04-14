import serial
import time

ser = serial.Serial('COM9', 115200, timeout=0.1)
time.sleep(2)  # Arduino reset moment

while True:
    cmd = input("Send byte (0-255, q to quit): ")

    if cmd == 'q':
        break

    pos = 1000

    high = (pos>> 8) & 0xFF;
    low = pos & 0xFF;

    # send
    ser.write(bytes([0x30, high, low]))

    # read response
    time.sleep(0.03)  # give Arduino time to respond
    response = ser.read_all()

    if response:
        print("Arduino says:", response)
    else:
        print("...silence... 👻")

ser.close()