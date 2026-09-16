import time
import serial
import requests

ser = serial.Serial('COM5', 9600)

url = 'https://api.binance.com/api/v3/ticker/price?symbol='

while True:
    try:
        coin = input("Enter a coin (Örn: BTCUSDT):")

        reply = requests.get(url+coin)

        if reply.status_code == 200:
            data = reply.json()

            price = float(data["price"])

            if coin == "BTCUSDT":
                data_send = f"{coin}:{price:.2f}\n"
            else:
                data_send = f"{coin}:{price:.3f}\n"

            ser.write(data_send.encode())

            print(f"Sent: {data_send.strip()}")

        time.sleep(5)

    except Exception as e:
        print("An error occurred; retrying:", e)
        time.sleep(5)
