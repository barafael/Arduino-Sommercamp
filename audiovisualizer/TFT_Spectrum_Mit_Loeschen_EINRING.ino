/***************************************************
  This is a library for the Adafruit 1.8" SPI display.

  This library works with the Adafruit 1.8" TFT Breakout w/SD card
  ----> http://www.adafruit.com/products/358
  The 1.8" TFT shield
  ----> https://www.adafruit.com/product/802
  The 1.44" TFT breakout
  ----> https://www.adafruit.com/product/2088
  as well as Adafruit raw 1.8" TFT display
  ----> http://www.adafruit.com/products/618

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include <math.h>

// For the breakout, you can use any 2 or 3 pins
// These pins will also work for the 1.8" TFT shield
#define TFT_CS     10
#define TFT_RST    9  // you can also connect this to the Arduino reset
// in which case, set this #define pin to 0!
#define TFT_DC     8
#define NOISE_LEVEL_0 500

// Option 1 (recommended): must use the hardware SPI pins
// (for UNO thats sclk = 13 and sid = 11) and pin 10 must be
// an output. This is much faster - also required if you want
// to use the microSD card (see the image drawing example)
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

// Option 2: use any pins but a little slower!
#define TFT_SCLK 13   // set these to be whatever pins you like!
#define TFT_MOSI 11   // set these to be whatever pins you like!
//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
#define BENCHMARK_PIN 3

float p = 3.1415926;
unsigned int Red = 0;
unsigned int Blue = 255;
int brightness = 0;
int Amp = 0;


void setup(void) {
  pinMode(BENCHMARK_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.print("Hello! ST7735 TFT Test");

  // Use this initializer if you're using a 1.8" TFT
  //tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab

  // Use this initializer (uncomment) if you're using a 1.44" TFT
  tft.initR(INITR_144GREENTAB);   // initialize a ST7735S chip, black tab

  Serial.println("Initialized");

  uint16_t time = millis();
  tft.fillScreen(ST7735_BLACK);
  time = millis() - time;

  Serial.println(time, DEC);
  delay(500);

  
  pinMode(A5, INPUT);
  pinMode(6, OUTPUT);



  Serial.println("done");
  delay(1000);
}


float grundRadius = 0;

void loop() {
  

  LautstaerkeMessung();
      //Serial.println(Amp);
        
  FarbBerechnung();
  
  //KreisLoeschen(grundRadius);

  
  //KreisLoeschen(grundRadius*3);
  
 
  //KreisLoeschen(grundRadius*5);

  
  
  RadienBerechnung();
  grundRadius = (int)round(grundRadius);
  //Serial.println(grundRadius);
  tft.fillScreen(ST7735_BLACK);
  Kreis(grundRadius, ConvertRGB(Red, 0, Blue));
  Kreis(grundRadius+3, ConvertRGB(Red, 0, Blue));

  
 
  
  
  
  
  
}

word ConvertRGB( byte R, byte G, byte B)
{
  return ( ((R & 0xF8) << 8) | ((G & 0xFC) << 3) | (B >> 3) );
}



void FarbBerechnung(){              //Berechnet Werte für Farben in Abhängigkeit von Lautstärke
  int percent = (int)Amp / 5;

  if(percent==50){ //LILA
    Blue = 255;
    Red = 255; 
  }

  else if(percent>50){ //ROT
    Red = 255;

    float differenz_pos = ((percent - 50.0)/50.0);
   // Serial.println(differenz_pos);
    
    Blue = 255 - ((int)(differenz_pos*255));       //mit Floats berechnen, dann in int abspeichern, sonst ist (percent - 50) /50 = 0 oder 1.
  }

  else if(percent < 50){ //BLAU
    Blue = 255;

    float differenz_neg = ((50.0 - percent)/50.0);
   // Serial.println(differenz_neg);
    
    Red = 255 - ((int)(differenz_neg*255));
  }
    
  
}



void LautstaerkeMessung(){
  digitalWrite(BENCHMARK_PIN, HIGH);
  int Volt = analogRead(A5);
  float next = MAF_next(Volt);
  if (Volt >= NOISE_LEVEL_0) {
    Amp = Volt - NOISE_LEVEL_0;
  }
  else if (Volt < NOISE_LEVEL_0) {
    Amp = NOISE_LEVEL_0 - Volt;
  }
  digitalWrite(BENCHMARK_PIN, LOW);
}

void Kreis(int r, int color){
  
  tft.drawCircle(64, 64, r, color);
  tft.drawCircle(64, 64, r+1, color);
  tft.drawCircle(64, 64, r+2, color);
  
}

void KreisLoeschen(int r){

  tft.drawCircle(64, 64, r, ST7735_BLACK);
  tft.drawCircle(64, 64, r+1, ST7735_BLACK);
  tft.drawCircle(64, 64, r+2, ST7735_BLACK);
}

void RadienBerechnung(){
  int percent = (int)Amp/5; 
  grundRadius = (percent/100.0)*61.0;
  
}

int marker = 0;
const int MAF_N = 32;
float values[MAF_N];
float MAF_next(float value) {
  marker = (marker + 1) % MAF_N;
  values[marker] = value;
  float sum = 0;
  for (size_t index = 0; index < MAF_N; index++) {
    sum += values[index];
  }
  return sum / MAF_N;
}
