import serial
import keyboard

ser = serial.Serial('COM10', 9600)

while True:
    if (ser.in_waiting > 0):
        gelen_veri = ser.readline().decode('utf-8').strip()
        print(gelen_veri)
        if gelen_veri == 'SES_ARTIR':
            keyboard.send('volume up')
        elif gelen_veri == 'SES_AZALT':
            keyboard.send('volume down')
        elif gelen_veri == 'DURDUR':
            keyboard.send("play/pause media")
        elif gelen_veri == 'ILERI':
            keyboard.send("next track")
        elif gelen_veri == 'GERI':
            keyboard.send("previous track")
        elif gelen_veri == 'MUTE':
            keyboard.send("volume mute")
        else:
            pass

