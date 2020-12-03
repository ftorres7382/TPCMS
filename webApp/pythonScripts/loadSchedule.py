import sys
import json
import serial
import time
COMPORT = '/dev/ttyACM0'
data = json.loads(sys.argv[1])
for x in data:
    data[x] = str(data[x])
    print(x + ":")
    print(data[x])
# try:
#     ser = serial.Serial(COMPORT, baudrate = 9600, timeout = .1)
# except Exception as e:
#     print(e)

# data = 0;
# while True:
#     time.sleep(1)
#     ser.write(b'Hello There\n')
#     while not data:
#         data = ser.read_until("\n").decode('ascii')        # reading the info from arduino and decoding it (ascii)
# 		print data
