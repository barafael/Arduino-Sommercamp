

/********************
 * 
 * Aus Beispiel "graphics" der Adafruit Library erstellt.
 * Aufbau am Arduino mit Mikrofon, TFT Display und Knopf.
 * Funktion: Audio Signal Interpretation in verschiedenen Versionen
 * Konstruiert mit Arduino UNO
 * Letzter Zustand (6) ohne Audiointerpretation
 * 
 ********************/


#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include <math.h>


#define TFT_CS     10
#define TFT_RST    9  

#define TFT_DC     8
#define NOISE_LEVEL_0 500
#define MINDEST_RADIUS 5
#define KNOPF_LESER 2
#define LED 5

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);


#define TFT_SCLK 13   
#define TFT_MOSI 11   

#define BENCHMARK_PIN 3

float p = 3.1415926;
unsigned int Red = 0;
unsigned int Blue = 255;
unsigned int Green = 0;
int brightness = 0;
double Amp = 0;
int radiusWarKlein = 0;



void setup(void) {
  pinMode(KNOPF_LESER, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(BENCHMARK_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.print("Hello! ST7735 TFT Test");

  
  tft.initR(INITR_144GREENTAB);   

  Serial.println("Initialized");

  uint16_t time = millis();
  tft.fillScreen(ST7735_BLACK);
  time = millis() - time;

  pinMode(A5, INPUT);
  pinMode(6, OUTPUT);

  tft.setCursor(30, 50);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextWrap(true);
  BigText( "Version 1");
  ScreenText("                                            Speaker");

  tft.fillScreen(ST7735_BLACK);



}


float grundRadius = 0;
int zustand = 1;

void loop() {

  while (zustand == 1) {                      //Drei Ringe ohne Radienwechsel

    LautstaerkeMessung();


    FarbBerechnung();

    Kreis(16, ConvertRGB(Red, 0, Blue));


    Kreis(32, ConvertRGB(Red, 0, Blue));


    Kreis(48, ConvertRGB(Red, 0, Blue));
    ButtonPressed();
  }

  while (zustand == 2) {
    LautstaerkeMessung();


    DreieckFarben();
    Dreiecke();
    ButtonPressed();
  }

  while (zustand == 3) {                        //Spektrum ohne Löschen (Drei Ringe)
    LautstaerkeMessung();


    FarbBerechnung();



    RadienBerechnung();
    grundRadius = (int)round(grundRadius);

    Kreis(grundRadius, ConvertRGB(Red, 0, Blue));


    Kreis(grundRadius * 3, ConvertRGB(Red, 0, Blue));


    Kreis(grundRadius * 5, ConvertRGB(Red, 0, Blue));


    ButtonPressed();
  }

  while (zustand == 4) {                    //Drei Ringe mit Radiusveränderung
    LautstaerkeMessung();


    FarbBerechnung();



    RadienBerechnung();
    grundRadius = (int)round(grundRadius);
    //Serial.println(grundRadius);

    if (grundRadius >= MINDEST_RADIUS) { //Threshhold
      Zeichnen();
      radiusWarKlein = 0;
    }
    else if (radiusWarKlein == 0) {
      ZeichnenKlein();
      radiusWarKlein = 1;
    }
    ButtonPressed();
  }

  while (zustand == 5) {                    //Ein Ring mit Radiusveränderung
    LautstaerkeMessung();
    //Serial.println(Amp);

    FarbBerechnung();

    RadienBerechnung();
    grundRadius = (int)round(grundRadius);
    //Serial.println(grundRadius);
    tft.fillScreen(ST7735_BLACK);
    Kreis((grundRadius * 4), ConvertRGB(Red, 0, Blue));
    Kreis((grundRadius * 4) + 3, ConvertRGB(Red, 0, Blue));
    ButtonPressed();
  }

  if (zustand == 6) {

    FarbVerlauf();
    
  }
}

word ConvertRGB( byte R, byte G, byte B)
{
  return ( ((R & 0xF8) << 8) | ((G & 0xFC) << 3) | (B >> 3) );
}

void FarbBerechnung() {             //Berechnet Werte für Farben in Abhängigkeit von Lautstärke
  int percent = (int)Amp / 5;

  if (percent == 50) { //LILA
    Blue = 255;
    Red = 255;
  }

  else if (percent > 50) { //ROT
    Red = 255;

    float differenz_pos = ((percent - 50.0) / 50.0);
    // Serial.println(differenz_pos);

    Blue = 255 - ((int)(differenz_pos * 255));     //mit Floats berechnen, dann in int abspeichern, sonst ist (percent - 50) /50 = 0 oder 1.
  }

  else if (percent < 50) { //BLAU
    Blue = 255;

    float differenz_neg = ((50.0 - percent) / 50.0);
    // Serial.println(differenz_neg);

    Red = 255 - ((int)(differenz_neg * 255));
  }
}

void DreieckFarben() {
  Red = 255;
  int percent = (int)Amp / 5;
  //Serial.println(percent);

  if (percent == 50) { //GELB
    Red = 255;
    Green = 255;
  }

  else if (percent > 50) { //GRÜN
    Green = 255;

    float differenz_pos = ((percent - 50.0) / 50.0);
    // Serial.println(differenz_pos);

    Red = 255 - ((int)(differenz_pos * 255));     //mit Floats berechnen, dann in int abspeichern, sonst ist (percent - 50) /50 = 0 oder 1.
  }

  else if (percent < 50) { //ROT
    Red = 255;

    float differenz_neg = ((50.0 - percent) / 50.0);
    // Serial.println(differenz_neg);

    Green = 255 - ((int)(differenz_neg * 255));
  }

}

#define FACTOR 60.0

void LautstaerkeMessung() {

  int Volt = analogRead(A5);
  float next = MAF_next(Volt);
  //Volt = (int) round(next);
  //Serial.println(next);
  if (Volt >= NOISE_LEVEL_0) {
    Amp = Volt - NOISE_LEVEL_0;

  }
  else if (Volt < NOISE_LEVEL_0) {
    Amp = NOISE_LEVEL_0 - Volt;
  }

}

void Kreis(int r, int color) {

  tft.drawCircle(64, 64, r, color);
  tft.drawCircle(64, 64, r + 1, color);
  tft.drawCircle(64, 64, r + 2, color);

}

void KreisLoeschen(int r) {

  tft.drawCircle(64, 64, r, ST7735_BLACK);
  tft.drawCircle(64, 64, r + 1, ST7735_BLACK);
  tft.drawCircle(64, 64, r + 2, ST7735_BLACK);
}

void RadienBerechnung() {
  int percent = (int)Amp / 5;
  grundRadius = (percent / 100.0) * 12.0;

}

int marker = 0;
const int MAF_N = 8;
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
void Zeichnen() {
  tft.fillScreen(ST7735_BLACK);


  Kreis(grundRadius, ConvertRGB(Red, 0, Blue));


  Kreis(grundRadius * 3, ConvertRGB(Red, 0, Blue));


  Kreis(grundRadius * 5, ConvertRGB(Red, 0, Blue));
}

void ZeichnenKlein() {
  tft.fillScreen(ST7735_BLACK);
  Kreis(MINDEST_RADIUS, ConvertRGB(Red, 0, Blue));

  Kreis(MINDEST_RADIUS * 3, ConvertRGB(Red, 0, Blue));

  Kreis(MINDEST_RADIUS * 5, ConvertRGB(Red, 0, Blue));
}

void ButtonPressed() {
  if (digitalRead(KNOPF_LESER) == HIGH) {
    analogWrite(LED, 255);
    delay(100);
    for (int i = 255; i > 0; i--) {
      analogWrite(LED, i);
      delay(3);
    }
    zustand++;


    if (zustand > 6) {
      zustand = 1;
    }

    tft.fillScreen(ST7735_BLACK);
    if (zustand == 1) {
      BigText( "Version 1");
      ScreenText("                                             Speaker");
      Blue = 0;
      Red = 0;
      Green = 0;
    }
    if (zustand == 2) {
      BigText( "Version 2");
      ScreenText("                                            Dreiecke");
    }
    if (zustand == 3) {
      BigText( "Version 3");
      ScreenText("                                            Spektrum");
    }
    if (zustand == 4) {
      BigText( "Version 4");
      ScreenText("                                         Drei bewegende           Kreise");
    }
    if (zustand == 5) {
      BigText( "Version 5");
      ScreenText("                                         Ein bewegender           Kreis");
    }



  }

  if (digitalRead(KNOPF_LESER) == LOW) {


    analogWrite(LED, 0);
  }
}

void ScreenText(String text) {
  tft.setTextSize(0);
  tft.setCursor(30, 50);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextWrap(true);
  tft.print(text);
  delay(1500);
  tft.fillScreen(ST7735_BLACK);
}

void BigText(String text) {
  tft.setTextSize(2);
  tft.setCursor(12, 40);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextWrap(true);
  tft.print(text);
}

void Dreiecke() {

  int w = (tft.width() / 2);
  int x = (tft.height() - 1) - 8;
  int y = 8;
  int z = tft.width() - 8;

  //tft.drawTriangle(w, y, y, x, z, x, ConvertRGB(Red, Green, 0)); Generell für Dreieck konstruktion.

  for (int t = 0; t <= 54; t += 6) {
    tft.drawTriangle(w, y + t, y + t, x - t, z - t, x - t, ConvertRGB(Red, Green, 0));
  }
}


void FarbVerlauf() {

  Red = 0;
  Green = 0;
  Blue = 255;

  while ((Red < 255) && (Blue == 255)) {
    tft.fillScreen(ConvertRGB(Red, 0, Blue));
    Red += 5;
    ButtonPressed();


    delay(1);                                      //Am Ende: Blue = 255, Red = 255
  }
  while ((Red == 255) && ((Blue > 0) && (Blue <= 255))) {
    tft.fillScreen(ConvertRGB(Red, 0, Blue));
    Blue -= 5;
    ButtonPressed();


    delay(1);                                       //Am Ende: Blue = 0, Red = 255
  }
  while ((Red == 255) && (Green < 255)) {
    tft.fillScreen(ConvertRGB(Red, Green, 0));
    Green += 5;
    ButtonPressed();


    delay(1);
  }
  while ((Green == 255) && ((Red > 0) && (Red <= 255))) {
    tft.fillScreen(ConvertRGB(Red, Green, 0));
    Red -= 5;
    ButtonPressed();


    delay(1);
  }
  while ((Green == 255) && ((Blue >= 0) && (Blue < 255))) {
    tft.fillScreen(ConvertRGB(0, Green, Blue));
    Blue += 5;
    ButtonPressed();


    delay(1);                                      //Am Ende: Blue = 255, Red = 255
  }
  while ((Green > 0) && (Blue == 255)) {
    tft.fillScreen(ConvertRGB(0, Green, Blue));
    Green -= 5;
    ButtonPressed();

    delay(1);                                      //Am Ende: Blue = 255, Red = 0 (ANFANG)
  }

}

