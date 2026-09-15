import time
import serial
import requests

ser = serial.Serial('COM5', 9600)

url = 'https://api.binance.com/api/v3/ticker/price?symbol='

while True:
    try:
        coin = input("Coin girin (Örn: BTCUSDT):")

        cevap = requests.get(url+coin)

        if cevap.status_code == 200:
            veri = cevap.json()

            price = float(veri["price"])

            if coin == "BTCUSDT":
                gonderilecek_veri = f"{coin}:{price:.2f}\n"
            else:
                gonderilecek_veri = f"{coin}:{price:.3f}\n"

            ser.write(gonderilecek_veri.encode())

            print(f"Gönderildi: {gonderilecek_veri.strip()}")

        time.sleep(5)

    except Exception as e:
        print("Bir hata oluştu, tekrar deneniyor:", e)
        time.sleep(5)