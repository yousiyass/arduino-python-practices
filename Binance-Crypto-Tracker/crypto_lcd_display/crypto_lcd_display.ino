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
    String gelen_veri = Serial.readStringUntil('\n');
    gelen_veri.trim();

    int iki_nokta = gelen_veri.indexOf(":");
    String coin_adi = gelen_veri.substring(0,iki_nokta);
    String coin_fiyati = gelen_veri.substring(iki_nokta+1);

    
    lcd.clear();
    tone(BUZZER_PIN, 2000, 50);
    lcd.setCursor(0, 0);
    lcd.print(coin_adi);
    lcd.print(":  ");
    lcd.setCursor(0,1);
    lcd.print("     ");
    lcd.print(coin_fiyati);
  }
}
