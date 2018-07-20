/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int LEDblau = 9;
int LEDgruen = 12;
int LEDgelb = 8;
int LEDrot = 7;
int TASTblau = 3;
int TASTgruen = 4;
int TASTgelb = 5;
int TASTrot = 6;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(LEDblau, OUTPUT); 
  pinMode(LEDgruen, OUTPUT); 
  pinMode(LEDgelb, OUTPUT);     
  pinMode(LEDrot, OUTPUT);     
    pinMode(TASTblau, INPUT);     
    pinMode(TASTgruen, INPUT);     
    pinMode(TASTgelb, INPUT);     
    pinMode(TASTrot, INPUT);
digitalWrite(TASTblau, HIGH);
digitalWrite(TASTgruen, HIGH);
digitalWrite(TASTgelb, HIGH);
digitalWrite(TASTrot, HIGH);


}

// the loop routine runs over and over again forever:

// the loop routine runs over and over again forever:
void loop() {
  boolean blauGedrueckt = digitalRead(TASTblau) == LOW;
  boolean gruenGedrueckt = digitalRead(TASTgruen) == LOW;
  boolean gelbGedrueckt = digitalRead(TASTgelb) == LOW;
  boolean rotGedrueckt = digitalRead(TASTrot) == LOW;

   if (blauGedrueckt){
    digitalWrite(LEDblau, HIGH);
  }
   if (gruenGedrueckt){
    digitalWrite(LEDgruen, HIGH);
  }
   if (gelbGedrueckt){
    digitalWrite(LEDgelb, HIGH);
  }
   if (rotGedrueckt){
    digitalWrite(LEDrot, HIGH); 
  }  // turn the LED on (HIGH is the voltage level)
                   // wait for a second  
 
  
  
}
