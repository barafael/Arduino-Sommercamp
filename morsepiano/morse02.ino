#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 7, 6, 5, 4);
int buffer = 0;
int input = 0;
int letterCount = 0;
  
void setup() {
  //LCD-Display
  lcd.begin(16, 2);
  
  //Button for short sounds
  pinMode(11, INPUT);
  digitalWrite(11, HIGH);
  
  //Button for long sounds
  pinMode(12, INPUT);
  digitalWrite(12, HIGH);
  
  //Button to end a letter
  pinMode(13, INPUT);
  digitalWrite(13, HIGH);
  
}

void loop() {
  //All of the following are set false in the beginning
  boolean btnShort = digitalRead(11) == LOW;
  boolean btnLong = digitalRead(12) == LOW;
  boolean btnEndLetter = digitalRead(13) == LOW;
  
  if (btnShort) {
    delay(225);
    input = 1;
    buffer = buffercalc(input, buffer);
  } else if (btnLong) {
    delay(225);
    input = 2;
    buffer = buffercalc(input, buffer);
  } else if (btnEndLetter) {
    delay(225);
    letterCount = letterCount + 1;
    buffer = letter(buffer);
    input = 0;
  }
}

int buffercalc(int input, int buffer) {
  buffer = buffer * 10;
  buffer = buffer + input;
  return buffer;
}

int letter(int buffer) {
  switch(buffer) {
    case 12:   lcd.print("A"); break;
    case 2111: lcd.print("B"); break;
    case 2121: lcd.print("C"); break;
    case 211:  lcd.print("D"); break;
    case 1:    lcd.print("E"); break;
    case 1121: lcd.print("F"); break;
    case 221:  lcd.print("G"); break;
    case 1111: lcd.print("H"); break;
    case 11:   lcd.print("I"); break;
    case 1222: lcd.print("J"); break;
    case 212:  lcd.print("K"); break;
    case 1211: lcd.print("L"); break;
    case 22:   lcd.print("M"); break;
    case 21:   lcd.print("N"); break;
    case 222:  lcd.print("O"); break;
    case 1221: lcd.print("P"); break;
    case 2212: lcd.print("Q"); break;
    case 121:  lcd.print("R"); break;
    case 111:  lcd.print("S"); break;
    case 2:    lcd.print("T"); break;
    case 112:  lcd.print("U"); break;
    case 1112: lcd.print("V"); break;
    case 122:  lcd.print("W"); break;
    case 2112: lcd.print("X"); break;
    case 2122: lcd.print("Y"); break;
    case 2211: lcd.print("Z"); break;
    case 2222: lcd.print(" "); break;
    case 2221: lcd.print("."); break;
    case 1122: lcd.print(","); break;
    case 1212: lcd.print("?"); break;
    default: lcd.print("!"); break;
  }
  // if letter is at the end of the first line: jump
  if (letterCount == 16) {
    lcd.setCursor(0, 1);
  }
  //if letter is near the end of the first line: jump
  else if (letterCount >= 10 && letterCount <= 16 && buffer == 2222) {
    lcd.setCursor(0, 1);
    letterCount = 16;
  }
  //if a space is at the end of the second line: clear
  else if (letterCount == 32) {
    letterCount = 0;
    lcd.clear();
  }
  //if a space is near the end of the second line: clear
  else if (letterCount >= 25 && buffer == 2222) {
    letterCount = 0;
    lcd.clear(); 
  }
  buffer = 0;
  return buffer;
}
