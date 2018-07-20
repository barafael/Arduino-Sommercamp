/***************************************************
  This is a library for our I2C LED Backpacks

  Designed specifically to work with the Adafruit LED Matrix backpacks
  ----> http://www.adafruit.com/products/872
  ----> http://www.adafruit.com/products/871
  ----> http://www.adafruit.com/products/870

  These displays use I2C to communicate, 2 pins are required to
  interface. There are multiple selectable I2C addresses. For backpacks
  with 2 Address Select pins: 0x70, 0x71, 0x72 or 0x73. For backpacks
  with 3 Address Select pins: 0x70 thru 0x77

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();

enum smilieState {SMILE, NEUTRAL, FROWN};
enum tamagotchiState { HUNGRY, TIRED, SLEEPING };

int currentTamagotchiState = SLEEPING;

SimpleTimer timer;

const int buttonPin = 12;

// variables will change:
int buttonState = 0;

void drawSmilie(uint8_t smilie[], int color) {
  matrix.clear();
  matrix.drawBitmap(0, 0, smilie, 8, 8, color);
  matrix.writeDisplay();
}

void setup() {
  Serial.begin(9600);
  Serial.println("Tamagotchi");

  matrix.begin(0x70);  // pass in the address
  pinMode(buttonPin, INPUT);
}


static const uint8_t
smile_bmp[] =
{ B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10100101,
  B10011001,
  B01000010,
  B00111100
};

static const uint8_t
neutral_bmp[] =
{ B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10111101,
  B10000001,
  B01000010,
  B00111100
};

static const uint8_t
frown_bmp[] =
{ B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10011001,
  B10100101,
  B01000010,
  B00111100
};

static const uint8_t
angry_bmp[] =
{
  B00111100,
  B01000010,
  B10100101,
  B10000001,
  B11010101,
  B10101011,
  B01000010,
  B00111100
};

static const uint8_t
heart_bmp[] =
{
  B00000000,
  B00000000,
  B01101100,
  B10010010,
  B10000010,
  B01000100,
  B00101000,
  B00010000,
};

static const uint8_t
fail_bmp[] =
{
  B11101110,
  B10001010,
  B11101110,
  B10001010,
  B01000100,
  B01000100,
  B01000100,
  B01000111,
};

void loop() {
  drawSmilie(neutral_bmp, LED_YELLOW);

  buttonState = digitalRead(buttonPin);


  if (buttonState == HIGH) {
    currentTamagotchiState = HUNGRY;
    Serial.println("I am really HUNGRY!");
    drawSmilie(frown_bmp, LED_RED);
  } else {
    return;
  }

  int button_counter = 0;
  long startTime = millis();
  while (millis() - startTime <= 10000) {
    buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH) {
      button_counter += 1;
    }
    delay(400);
  }
  if (button_counter >= 3) {
    drawSmilie(smile_bmp, LED_GREEN);
  }
  else {
    drawSmilie(frown_bmp, LED_YELLOW);
  }

  delay(200);

}

