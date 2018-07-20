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
int current = NEUTRAL;
const int buttonPin = 12;     // the number of the pushbutton pin


// variables will change:
int buttonState = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("8x8 LED Matrix Test");

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
},
neutral_bmp[] =
{ B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10111101,
  B10000001,
  B01000010,
  B00111100
},
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

void loop() {
  buttonState = digitalRead(buttonPin);
  switch (current) {
    case NEUTRAL:
      drawSmilie(neutral_bmp, LED_YELLOW);
      if (buttonState == HIGH) {
        current = SMILE;
      }
      break;
    case SMILE:
      drawSmilie(smile_bmp, LED_GREEN);
      if (buttonState == HIGH) {
        current = FROWN;
      }

      break;
    case FROWN :
      drawSmilie(frown_bmp, LED_RED);
      if (buttonState == HIGH) {
        current = NEUTRAL;
      }
      break;
  }
  delay(200);

}

void drawSmilie(uint8_t smilie[], int color) {

  matrix.clear();
  matrix.drawBitmap(0, 0, smilie, 8, 8, color);
  matrix.writeDisplay();
}

