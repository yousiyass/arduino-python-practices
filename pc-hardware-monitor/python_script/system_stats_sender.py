import time
import psutil
import GPUtil
import serial

ser = serial.Serial('COM10',9600)

while True:
    cpu = psutil.cpu_percent()
    gpu = GPUtil.getGPUs()[0].temperature

    veri = f"CPU:%{cpu} GPU:{gpu}C\n"

    ser.write(veri.encode())
    time.sleep(2)

