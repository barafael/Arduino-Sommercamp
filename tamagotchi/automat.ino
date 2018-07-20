#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include <SimpleTimer.h>

Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();

#include"smilieBMP.h"

int x, y, z;
float x_smooth, y_smooth, z_smooth;
long x_sm, y_sm, z_sm;

#define X_PIN 0
#define Y_PIN 1
#define Z_PIN 2

enum TamagotchiState { SLEEPING, SMILE, NEUTRAL, FROWN, AWAKE, TIRED, HUNGRY, ALONE, FAIL, HEART };
enum TamagotchiNeeds { FOOD, REST, DONATION };

TamagotchiState tamagotchiState = SLEEPING;

const int buttonPin = 12;
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
 drawSmilie(sleep_bmp, LED_YELLOW); 

  randomSeed(analogRead(0));
}

void loop() {
  /*readAcc();
  Serial.println(x_sm);
  if (x_sm>310){
    tamagotchiState = FROWN;*/

  // Buttons auslesen...
 /* drawSmilie(neutral_bmp, LED_YELLOW);*/
  int Zufallszustand = 0;
  long startTime = 0;
  int smileCounter = 0;
  int buttonCounter = 0;
  int numberSmiley = 0;


  buttonState = digitalRead(buttonPin);
  buttonCounter = 0;
  switch (tamagotchiState) {
    case SLEEPING:
      Serial.println("I am SLEEPING!");
      delay(2000);
      if (buttonState == HIGH) {
        drawSmilie(neutral_bmp, LED_YELLOW);
        tamagotchiState = HUNGRY;
        Serial.println("I am really HUNGRY!");
      }
      break;
       
       /*readAcc();
        Serial.println(x_sm);
        if (x_sm>400){
        tamagotchiState = FROWN;
        }*/

    case NEUTRAL:
      if (numberSmiley < 8) {
        drawSmilie(neutral_bmp, LED_YELLOW);
        delay (5000);
        Zufallszustand = random(1, 3);
        switch (Zufallszustand) {
          case 1:
            tamagotchiState = HUNGRY;
            break;
         /* case 2:
            tamagotchiState = ALONE;
            break; */
          case 2:
            tamagotchiState = TIRED;
            break;
        }
      }
      else if ( smileCounter >= 6) {
        tamagotchiState = HEART;
      }
      else {
        tamagotchiState = FAIL;
      }
      break;

    case HUNGRY:
      Serial.println("I am really HUNGRY!");
      buttonCounter = 0;
      startTime = millis();
      while (millis() - startTime <= 10000) {
        buttonState = digitalRead(buttonPin);
        if  (buttonState == HIGH) {
          buttonCounter += 1;
        }
      }
      if (buttonCounter >= 3) {
        tamagotchiState = SMILE;
      }
      else {
        tamagotchiState = FROWN;
      }
      break;

   /* case ALONE:
      Serial.println("I am really ALONE!");
      tamagotchiState = NEUTRAL;
      break;
*/
    case FROWN:
      drawSmilie(frown_bmp, LED_RED);
      delay(5000);
      tamagotchiState = NEUTRAL;
      numberSmiley++;
      break;

    case AWAKE:
      Serial.println("I am AWAKE!");
      buttonCounter = 0;
      startTime = millis();
      while (millis() - startTime <= 1000) {
        buttonState = digitalRead(buttonPin);
        if (buttonState == HIGH) {
          buttonCounter += 1;
        }
        delay(200);
      }
      if (buttonCounter >= 1) {
        tamagotchiState = SMILE;
      }
      else {
        tamagotchiState = FROWN;
      }
      break;

    case SMILE:
      drawSmilie(smile_bmp, LED_GREEN);
      delay (10000);
      tamagotchiState = NEUTRAL;
      smileCounter++;
      numberSmiley++;
      break;

    case TIRED:
      Serial.println("I am really TIRED!");
      tamagotchiState = NEUTRAL;
      //noch kalibiren
      break;

    case HEART:
      drawSmilie(heart_bmp, LED_RED);
      break;

    case FAIL:
      drawSmilie(fail_bmp, LED_RED);
      break;

      delay(100);
  }
}

#define MAF_SIZE 16

typedef struct MAF_data {
  size_t marker = 0;
  float values[MAF_SIZE];
} MAF_data;

MAF_data x_data;
MAF_data y_data;
MAF_data z_data;

float MAF_next(struct MAF_data *data, float value) {

  data->marker = (data->marker + 1) % MAF_SIZE;
  data->values[data->marker] = value;
  float sum = 0;
  for (size_t index = 0; index < MAF_SIZE; index++) {
    sum += data->values[index];
  }
  return sum / MAF_SIZE;
}

//#define ACC_PRINT

void readAcc() {
  x = analogRead(X_PIN);
  y = analogRead(Y_PIN);
  z = analogRead(Z_PIN);

  int startTime = millis();
  int counter = 0;
  while (millis() - startTime < 1000) {
    x_smooth = MAF_next(&x_data, x);
    y_smooth = MAF_next(&y_data, y);
    z_smooth = MAF_next(&z_data, z);
    delay(10);
    x_sm += x_smooth;
    y_sm += y_smooth;
    z_sm += z_smooth;
    counter++;
  }
  x_sm /= counter;
  y_sm /= counter;
  z_sm /= counter;
  
/* #ifdef ACC_PRINT
 Serial.print("accelerations are x, y, z: ");
  Serial.print(x_smooth, DEC);    // print the acceleration in the X axis
  Serial.print(" ");       // prints a space between the numbers
  Serial.print(y_smooth, DEC);    // print the acceleration in the Y axis
  Serial.print(" ");       // prints a space between the numbers
  Serial.println(z_smooth, DEC);  // print the acceleration in the Z axis
#endif */
}

