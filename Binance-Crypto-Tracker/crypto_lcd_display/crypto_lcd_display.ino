#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define BUZZER_PIN 7

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  if(Serial.available() > 0) {
    String incoming_data = Serial.readStringUntil('\n');
    incoming_data.trim();

    int colon = incoming_data.indexOf(":");
    String coin_name = incoming_data.substring(0,colon);
    String coin_price = incoming_data.substring(colon+1);

    
    lcd.clear();
    tone(BUZZER_PIN, 2000, 50);
    lcd.setCursor(0, 0);
    lcd.print(coin_name);
    lcd.print(":  ");
    lcd.setCursor(0,1);
    lcd.print("     ");
    lcd.print(coin_price);
  }
}
