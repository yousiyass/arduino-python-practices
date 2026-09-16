# Binance Crypto Tracker 📈

**Project Date:** July 14, 2026

## Overview
This project is a hardware-software integration that tracks live cryptocurrency prices. A Python script runs on the PC to fetch real-time data (e.g., from Binance) and sends it via serial communication. The Arduino board receives this parsed data, triggers a buzzer notification, and displays the coin name and current price on an I2C LCD display.

![BTC Live Tracking](images/btc_test.jpg)
![ETH Live Tracking](images/eth_test.jpg)

## Technologies Used
* **Hardware:** Arduino Uno, I2C 16x2 LCD Display, Buzzer
* **Software:** C++ (Arduino IDE), Python (requests, pyserial)
* **Key Concepts:** Serial Communication, API Integration, String Parsing, I2C Protocol

## Project Structure
* `/crypto_lcd_display`: Contains the `.ino` file for the Arduino microcontroller.
* `/python_script`: Contains the `.py` script responsible for fetching and transmitting the data over the COM port.

## Hardware Wiring
* **I2C LCD Display:** SDA -> A4, SCL -> A5, VCC -> 5V, GND -> GND
* **Buzzer:** Positive Pin -> Digital Pin 7, Negative Pin -> GND

## How to Run
1. Upload the `.ino` sketch to your Arduino.
2. Install the required Python libraries:
   ```bash
   pip install pyserial requests
