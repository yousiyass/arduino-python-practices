import serial
import keyboard

ser = serial.Serial('COM10', 9600)

while True:
    if (ser.in_waiting > 0):
        incoming_data = ser.readline().decode('utf-8').strip()
        print(incoming_data)
        if incoming_data == 'volume_up':
            keyboard.send('volume up')
        elif incoming_data == 'volume_down':
            keyboard.send('volume down')
        elif incoming_data == 'stop':
            keyboard.send("play/pause media")
        elif incoming_data == 'next_track':
            keyboard.send("next track")
        elif incoming_data == 'prev_track':
            keyboard.send("previous track")
        elif incoming_data == 'mute':
            keyboard.send("volume mute")
        else:
            pass

