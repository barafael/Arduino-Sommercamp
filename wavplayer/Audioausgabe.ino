#include <TMRpcm.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

#define TFT_CS     10
#define TFT_RST    3
#define TFT_DC     8

TMRpcm tmrpcm;
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

void setup() {
  tmrpcm.speakerPin = 9;
  Serial.begin(9600);
  while (!Serial);
  tft.initR(INITR_144GREENTAB);
  tft.fillScreen(ST77XX_BLACK);
  
  if (!SD.begin(4))
    Serial.println("SD fail");
  else {
    uint16_t time = millis();
    time = millis() - time;
    tft.fillScreen(ST77XX_BLACK);
    testdrawtext("Hallo Welt, das ist ein Test!", ST77XX_WHITE);

  }
}

void loop() {
  tmrpcm.play("piano3.wav");
  
  delay(5000);
}


void testdrawtext(char *text, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

