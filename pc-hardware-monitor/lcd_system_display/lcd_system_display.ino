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
    String incoming_data = Serial.readStringUntil('\n');

    //CPU Discovery
    int start1 = incoming_data.indexOf("CPU:%") + 5;
    int finish1 = incoming_data.indexOf("GPU:") - 2;
    String merge1 = incoming_data.substring(start1, finish1);
    int cpu = merge1.toInt();

    //GPU Discovery
    int start2 = incoming_data.indexOf("GPU:") + 4;
    int finish2 = incoming_data.indexOf("C") - 1;
    String merge2 = incoming_data.substring(start2, finish2);
    int gpu = merge2.toInt();


    lcd.setCursor(0, 0);
    lcd.print("CPU: %");
    lcd.print(cpu);
    
    lcd.setCursor(0,1);
    lcd.print("GPU: ");
    lcd.print(gpu);
    lcd.print("C");

  }
}
