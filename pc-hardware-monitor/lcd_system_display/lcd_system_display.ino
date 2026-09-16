#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
}

void loop() {
  if (Serial.available() > 0) {
    String gelen_veri = Serial.readStringUntil('\n');

    //CPU BULMA
    int basla1 = gelen_veri.indexOf("CPU:%") + 5;
    int bitir1 = gelen_veri.indexOf("GPU:") - 2;
    String birlestir1 = gelen_veri.substring(basla1, bitir1);
    int cpu = birlestir1.toInt();

    //GPU BULMA
    int basla2 = gelen_veri.indexOf("GPU:") + 4;
    int bitir2 = gelen_veri.indexOf("C") - 1;
    String birlestir2 = gelen_veri.substring(basla2, bitir2);
    int gpu = birlestir2.toInt();


    lcd.setCursor(0, 0);
    lcd.print("CPU: %");
    lcd.print(cpu);
    
    lcd.setCursor(0,1);
    lcd.print("GPU: ");
    lcd.print(gpu);
    lcd.print("C");

  }
}
