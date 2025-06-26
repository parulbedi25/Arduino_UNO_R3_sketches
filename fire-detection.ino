#include <LiquidCrystal.h>
LiquidCrystal lcd(4, 5, 6, 7, 8, 12);

const int dataPin = 9;
const int latchPin = 10;
const int clockPin = 11;

const int mq135Pin = A0;
const int buzzerPin = 13;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Alcohol Detector");

  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  delay(5000);
  lcd.clear();
}

void loop() {
  int alcoholValue = analogRead(mq135Pin);

  int level;
   String levelMsg;

  if (alcoholValue < 200) {
      level = 1;
    levelMsg = "No Alcohol";
  } 
  else if (alcoholValue < 300) {
     level = 2;
      levelMsg = "Low Alcohol";
  } 
  else if (alcoholValue < 400) {
    level = 3;
    levelMsg = "Medium Alcohol";
  } 
  else {
    level = 4;
     levelMsg = "High Alcohol";
  }

  lcd.setCursor(0, 0);
  String line1 = String(level) + ": " + levelMsg;
  lcd.print(line1);

  for (int i = line1.length(); i < 16; i++) {
    lcd.print(" ");
  }

  lcd.setCursor(0, 1);
  lcd.print("Value: ");
  lcd.print(alcoholValue);
  lcd.print("    ");

  int ledLevel = map(alcoholValue, 0, 1023, 0, 10);
  byte ledPattern = (ledLevel == 0) ? 0x00 : (1 << ledLevel) - 1;

  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, ledPattern);
  digitalWrite(latchPin, HIGH);

  if (level == 4) {
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
    delay(100);
  } else {
    digitalWrite(buzzerPin, LOW);
    delay(200);
  }
}
