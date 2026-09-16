import time
import psutil
import GPUtil
import serial

ser = serial.Serial('COM10',9600)

while True:
    cpu = psutil.cpu_percent()
    gpu = GPUtil.getGPUs()[0].temperature

    data = f"CPU:%{cpu} GPU:{gpu}C\n"

    ser.write(data.encode())
    time.sleep(2)

