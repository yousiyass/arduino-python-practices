import serial
import time
import sqlite3


ser = serial.Serial('COM10', 9600)


db = sqlite3.connect("../safe_logs.db")
cursor = db.cursor()
cursor.execute("CREATE TABLE IF NOT EXISTS ACCESS_LOGS (timestamp TEXT, log_message TEXT)")
db.commit()

print("Security system listening. Waiting for logs...")

failed_attempts = 0

while True:
    if ser.in_waiting > 0:
        incoming_data = ser.readline().decode('utf-8', errors='ignore').strip()

        if incoming_data == "ACCESS_GRANTED" or incoming_data == "ACCESS_DENIED":

            if incoming_data == "ACCESS_GRANTED":
                log_message = "Access Granted!"
                failed_attempts = 0
            else:
                failed_attempts += 1
                if failed_attempts >= 3:
                    log_message = "WARNING: 3rd failed attempt! System locking down..."
                    ser.write("KILIT\n".encode('utf-8'))
                else:
                    attempts_left = 3 - failed_attempts
                    log_message = f"ALERT: Wrong password attempt. (Attempts left: {attempts_left})"

            timestamp = time.strftime("%d/%m/%Y, %H:%M:%S")
            cursor.execute("INSERT INTO ACCESS_LOGS VALUES (?, ?)", (timestamp, log_message))
            db.commit()

            cursor.execute("SELECT * FROM ACCESS_LOGS")
            records = cursor.fetchall()

            print("\n--- SECURITY LOG RECORDS ---")
            for row in records:
                print(f"Time: {row[0]} | Status: {row[1]}")