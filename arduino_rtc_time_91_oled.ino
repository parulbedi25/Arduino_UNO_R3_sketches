#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
#define DS3231_I2C_ADDRESS 0x68

#define SET_RTC_TIME false

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


const unsigned char sun_bitmap[] PROGMEM = {
  0b00000001, 0b10000000,
  0b00001001, 0b10010000,
  0b00000111, 0b11100000,
  0b00001111, 0b11110000,
  0b00111111, 0b11111100,
  0b00111111, 0b11111100,
  0b01111111, 0b11111110,
  0b01111111, 0b11111110,
  0b01111111, 0b11111110,
  0b01111111, 0b11111110,
  0b00111111, 0b11111100,
  0b00111111, 0b11111100,
  0b00001111, 0b11110000,
  0b00000111, 0b11100000,
  0b00001001, 0b10010000,
  0b00000001, 0b10000000
};


const unsigned char moon_bitmap[] PROGMEM = {
  0b00000111, 0b11000000,
  0b00011111, 0b11100000,
  0b00111100, 0b01110000,
  0b01110000, 0b00111000,
  0b01100000, 0b00011100,
  0b11100000, 0b00001110,
  0b11000000, 0b00000110,
  0b11000000, 0b00000000,
  0b11000000, 0b00000000,
  0b11000000, 0b00000000,
  0b11100000, 0b00000110,
  0b01100000, 0b00001110,
  0b01110000, 0b00011100,
  0b00111100, 0b01111000,
  0b00011111, 0b11110000,
  0b00000111, 0b11100000
};

bool rtcAvailable = false;

void setup() {
  Wire.begin();
  Serial.begin(9600);

  // OLED init
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED failed"));
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Check if RTC is connected
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  if (Wire.endTransmission() == 0) {
    rtcAvailable = true;
    Serial.println("RTC detected");
  } else {
    rtcAvailable = false;
    Serial.println("RTC not detected!");
  }

  // Set RTC time only once
#if SET_RTC_TIME
  if (rtcAvailable) {
  // Set initial time: seconds, minutes, hours, dayOfWeek (1=Sun), dayOfMonth, month, year
  // setDS3231time(0, 10, 14, 1, 8, 6, 25); // e.g. "2:10:00 PM Sunday 08/06- May/2025"
    setDS3231time(0, 54, 15, 1, 8, 6, 25);  // hh:mm:ss dow dd/mm/yy
    Serial.println("RTC time set.");
  }
#endif
}

void loop() {
  if (rtcAvailable) {
    displayTime();
  } else {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("RTC NOT CONNECTED");
    display.display();
  }
  delay(1000);
}

void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year) {
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0x00);
  Wire.write(decToBcd(second));
  Wire.write(decToBcd(minute));
  Wire.write(decToBcd(hour));
  Wire.write(decToBcd(dayOfWeek));
  Wire.write(decToBcd(dayOfMonth));
  Wire.write(decToBcd(month));
  Wire.write(decToBcd(year));
  Wire.endTransmission();
}

void readDS3231time(byte *second, byte *minute, byte *hour,
                    byte *dayOfWeek, byte *dayOfMonth, byte *month, byte *year) {
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0x00);
  Wire.endTransmission();

  Wire.requestFrom(DS3231_I2C_ADDRESS, 7);
  *second = bcdToDec(Wire.read() & 0x7F);
  *minute = bcdToDec(Wire.read());
  *hour = bcdToDec(Wire.read() & 0x3F);
  *dayOfWeek = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month = bcdToDec(Wire.read());
  *year = bcdToDec(Wire.read());
}

void displayTime() {
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);

  const char* days[] = {"", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

  bool isPM = false;
  byte displayHour = hour;
  if (hour == 0) {
    displayHour = 12;
    isPM = false;
  } else if (hour == 12) {
    displayHour = 12;
    isPM = true;
  } else if (hour > 12) {
    displayHour = hour - 12;
    isPM = true;
  }

  display.clearDisplay();

  // Row 1: Date
  display.setCursor(0, 0);
  if (dayOfMonth < 10) display.print("0");
  display.print(dayOfMonth);
  display.print("/");
  if (month < 10) display.print("0");
  display.print(month);
  display.print("/20");
  if (year < 10) display.print("0");
  display.print(year);

  // Row 2: Time + AM/PM
  display.setCursor(0, 10);
  if (displayHour < 10) display.print("0");
  display.print(displayHour);
  display.print(":");
  if (minute < 10) display.print("0");
  display.print(minute);
  display.print(":");
  if (second < 10) display.print("0");
  display.print(second);
  display.print(" ");
  display.print(isPM ? "PM" : "AM");

  // Row 3: Day name
  display.setCursor(0, 22);
  display.print(days[dayOfWeek]);

  int iconX = 105;
  int iconY = 0;
  display.drawBitmap(iconX, iconY, isPM ? moon_bitmap : sun_bitmap, 16, 16, SSD1306_WHITE);

  display.display();
}

byte decToBcd(byte val) {
  return (val / 10 * 16) + (val % 10);
}
byte bcdToDec(byte val) {
  return (val / 16 * 10) + (val % 16);
}
