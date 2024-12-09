#include <Arduino.h>
#include <TFT_eSPI.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_CAP1188.h>
#define TFT_GREY 0x5AEB
#define CAP1188_RESET  9
#define CAP1188_CS  10
#define CAP1188_MOSI  11
#define CAP1188_MISO  12
#define CAP1188_CLK  13
TFT_eSPI tft = TFT_eSPI();

// for timer 
unsigned long previousMillis = 0;
const long interval = 1000; // 1 second interval
bool isWholeSecond = true;
Adafruit_CAP1188 cap = Adafruit_CAP1188(); // I2C
//Adafruit_CAP1188 cap = Adafruit_CAP1188(CAP1188_CLK, CAP1188_MISO, CAP1188_MOSI, CAP1188_CS, CAP1188_RESET); // SPI

void setup() {
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  if (!cap.begin(0x28)) { // I2C
  // if (!cap.begin()) { // SPI
    tft.println("CAP1188 not found");
    while (1);
  }
}

void loop() {
  unsigned long currentMillis = millis();

  int count = 0;
  tft.setTextColor(TFT_WHITE, TFT_RED);
  tft.setTextSize(2);
  // timer print
  if (currentMillis - previousMillis >= interval)
    {
      previousMillis = currentMillis;
      isWholeSecond = !isWholeSecond;
      if (isWholeSecond)
      {
        tft.setCursor(30, 50, 2);
        tft.print("Time elapsed: ");
        tft.println(currentMillis);
      }
    }

  uint8_t touched = cap.touched();
  int num_touched = 0;
  for (uint8_t i=0; i<8; i++) {
    if (touched & (1 << i)) {
      num_touched++;
    }
  }
  tft.print("Num Sensors Touched: ");
  tft.println(num_touched);
  
}