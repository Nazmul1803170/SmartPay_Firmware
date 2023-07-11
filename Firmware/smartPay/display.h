#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define BUZ_PIN 15

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 32  // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void configDisplay() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    for (;;)
      ;
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println("smart-PAY");
  display.display();
}

void showText(String txt, int size, int r, int c,bool clr) {
  if(clr)
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(size);
  display.setCursor(r, c);
  display.println(txt);
  display.display();
}

void buzzer() {
  digitalWrite(BUZ_PIN, HIGH);
  delay(1000);
  digitalWrite(BUZ_PIN, LOW);
}