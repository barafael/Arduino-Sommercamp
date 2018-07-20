#include <LiquidCrystal.h>

void setup() {
  //LCD-Display
  LiquidCrystal lcd(2, 3, 7, 6, 5, 4);
  lcd.begin(16, 2);
  
  //Button for short sounds
  int pinShort = 11;
  pinMode(pinShort, INPUT);
  digitalWrite(pinShort, HIGH);
  
  //Button for long sounds
  int pinLong = 12;
  pinMode(pinLong, INPUT);
  digitalWrite(pinLong, HIGH);
  
  //Button to end a letter
  int pinEnd = 13;
  pinMode(pinEnd, INPUT);
  digitalWrite(pinEnd, HIGH);
  
  //All of the following are set false in the beginning
  boolean btnShort = digitalRead(pinShort) == LOW;
  boolean btnLong = digitalRead(pinLong) == LOW;
  boolean btnEndLetter = digitalRead(pinEnd) == LOW;
}

void loop() {
  int input = 1;
  int buffer = 0;
  
  while (input != 3) { // 3 is the button to end a word
    buffer = buffer * 10;
    buffer = buffer + input;
    if (btnShort) {
      delay(200);
      input = 1;
    } else if (btnLong) {
      delay(200);
      input = 2;
    } else if (btnEndLetter) {
      delay(200);
      input = 3; 
    }
  }
  
  char letter;
  switch(buffer) {
    case 12:   letter = "A"; break;
    case 2111: letter = "B"; break;
    case 2121: letter = "C"; break;
    case 211:  letter = "D"; break;
    case 1:    letter = "E"; break;
    case 1121: letter = "F"; break;
    case 221:  letter = "G"; break;
    case 1111: letter = "H"; break;
    case 11:   letter = "I"; break;
    case 1222: letter = "J"; break;
    case 212:  letter = "K"; break;
    case 1211: letter = "L"; break;
    case 22:   letter = "M"; break;
    case 21:   letter = "N"; break;
    case 222:  letter = "O"; break;
    case 1221: letter = "P"; break;
    case 2212: letter = "Q"; break;
    case 121:  letter = "R"; break;
    case 111:  letter = "S"; break;
    case 2:    letter = "T"; break;
    case 112:  letter = "U"; break;
    case 1112: letter = "V"; break;
    case 122:  letter = "W"; break;
    case 2112: letter = "X"; break;
    case 2122: letter = "Y"; break;
    case 2211: letter = "Z"; break;
    case 2222: letter = " "; break;
    default: letter = "!"; break;
  }
  lcd.print(letter);
  
}
