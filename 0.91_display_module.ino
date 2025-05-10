#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/FreeMono12pt7b.h>
#include <Fonts/FreeMono18pt7b.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

String text = "Hi! Parul Bedi";
int textSize = 3;
int scrollSpeed = 0;

int16_t xPos;
int16_t textWidth;
uint32_t scrollTimer = 0;
void applyTextSize(int size) {
  switch (size) {
    case 1:
      display.setFont(&FreeMono9pt7b);
      break;
    case 2:
      display.setFont(&FreeMono12pt7b);
      break;
    case 3:
      display.setFont(&FreeMono18pt7b);
      break;
    default:
      display.setFont(&FreeMono9pt7b);
      break;
  }
}

void setup() {
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }

  display.setTextColor(SSD1306_WHITE);
  display.setTextWrap(false);
  
  applyTextSize(textSize);

  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(text, 0, 20, &x1, &y1, &w, &h);
  textWidth = w;
  xPos = SCREEN_WIDTH;
}

void loop() {
  display.clearDisplay();
  applyTextSize(textSize);

  display.setCursor(xPos, 24);
  display.print(text);
  display.display();

  if (textWidth > SCREEN_WIDTH) {
    if (millis() - scrollTimer > scrollSpeed) {
      xPos--;
      scrollTimer = millis();
    }

    if (xPos < -textWidth) {
      xPos = SCREEN_WIDTH;
    }
  } else {
    xPos = (SCREEN_WIDTH - textWidth) / 2;
  }
}
