#include <IRremote.hpp>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define LED_RED 9
#define LED_GREEN 10
#define IR_PIN 8
#define BUZZER_PIN 7

bool is_locked = false;


unsigned int map_ir_to_digit(int ir_code) {
  if (ir_code == 4)  return 1;
  if (ir_code == 5)  return 2;
  if (ir_code == 6)  return 3;
  if (ir_code == 8)  return 4;
  if (ir_code == 9)  return 5;
  if (ir_code == 10) return 6;
  if (ir_code == 12) return 7;
  if (ir_code == 13) return 8;
  if (ir_code == 14) return 9;
  if (ir_code == 17) return 0;
  return 99; 
}

void success_feedback() {
  digitalWrite(LED_GREEN, HIGH); 
  
  tone(BUZZER_PIN, 1200, 100);
  delay(120);
  tone(BUZZER_PIN, 1600, 100);
  delay(120);
  tone(BUZZER_PIN, 2400, 250);
  
  delay(1000); 
  digitalWrite(LED_GREEN, LOW);  
}

void error_feedback() {
  digitalWrite(LED_RED, HIGH); 
  
  tone(BUZZER_PIN, 200, 250);
  delay(300);
  tone(BUZZER_PIN, 200, 250);
  
  delay(700); 
  digitalWrite(LED_RED, LOW);  
}

int password[6] = {1, 2, 1, 1, 0, 6};
int entered_password[6];
int digit_count = 0;

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  IrReceiver.begin(IR_PIN);

  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, LOW);

  lcd.setCursor(0, 0);
  lcd.print("Enter Password:");
  delay(2000);
  lcd.clear();
}

void loop() {

  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n'); 
    command.trim(); 

    if (command == "KILIT") {
      is_locked = true; 
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("SYSTEM LOCKED!");
      lcd.setCursor(0, 1);
      lcd.print("ACCESS DENIED");
      digitalWrite(LED_RED, HIGH);
      tone(BUZZER_PIN, 1200, 1500);
    }
  }


  if (!is_locked) {
    if (IrReceiver.decode()) {
      int ir_result = IrReceiver.decodedIRData.command;
      int digit = map_ir_to_digit(ir_result);

      if (digit != 99) { 
        entered_password[digit_count] = digit;
        digit_count++;

        lcd.setCursor(digit_count, 0);
        lcd.print(digit);
        
        tone(BUZZER_PIN, 1200, 50);
        delay(50);
        noTone(BUZZER_PIN);
      }
      
      IrReceiver.begin(8, ENABLE_LED_FEEDBACK); 

  
      if (digit_count == 6) {
        bool is_correct = true;

        for (int i = 0; i < 6; i++) { 
          if (entered_password[i] != password[i]) {
            is_correct = false;
            break;
          }
        }
        
        if (is_correct) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Password OK");
          lcd.setCursor(0, 1);
          lcd.print("Access Granted");
          Serial.println("ACCESS_GRANTED");
          
          success_feedback(); 
        } 
        else {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Wrong Password");
          lcd.setCursor(0, 1);
          lcd.print("Try Again");
          Serial.println("ACCESS_DENIED");
          
          error_feedback(); 
          lcd.clear();     
        }

        digit_count = 0; 
        IrReceiver.begin(8, ENABLE_LED_FEEDBACK);
      }
      delay(1000);
      IrReceiver.resume();
    }
  }
}