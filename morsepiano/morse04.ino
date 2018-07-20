#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 7, 6, 5, 4);
int tmp = 0;
int input = 0;
int letterCount = 0;
int led = 8;
  
/* Initializes the Arduino
 *
 */
void setup() {
  // LCD-Display
  lcd.begin(16, 2);
  
  // Button for short sounds
  pinMode(11, INPUT);
  digitalWrite(11, HIGH);
  
  // Button for long sounds
  pinMode(12, INPUT);
  digitalWrite(12, HIGH);
  
  // Button to end a letter
  pinMode(13, INPUT);
  digitalWrite(13, HIGH);
  
  // Buzzer
  pinMode(9, OUTPUT);
  
  // LED blau
  pinMode(8, OUTPUT);

  // LED grün
  pinMode(10, OUTPUT);
}

void loop() {
  // All of the following are set false in the beginning
  boolean btnShort = digitalRead(11) == LOW;
  boolean btnLong = digitalRead(12) == LOW;
  boolean btnEndLetter = digitalRead(13) == LOW;
  
  if (btnShort) {
    delay(250);
    input = 1;
    tmp = buffercalc(input, tmp);
    tone(9, 440, 100); // Buzzer
    analogWrite(led, 150); // LED
    delay(100); // LED
    analogWrite(led, 0);
  }
  else if (btnLong) {
    delay(250);
    input = 2;
    tmp = buffercalc(input, tmp);
    tone(9, 440, 300); // Buzzer
    analogWrite(led, 150); // LED
    delay(300); // LED
    analogWrite(led, 0);
  }
  else if (btnEndLetter) {
    delay(250);
    letterCount = letterCount + 1;
    tmp = letter(tmp);
    input = 0;
    // Change of LED
    if (led == 8) {
      led = 10;
    } else {
      led = 8;
    }
  }
}

int buffercalc(int input, int tmp) {
  tmp = tmp * 10;
  tmp = tmp + input;
  return tmp;
}

int letter(int tmp) {
  if (letterCount != 0) {
    letterCount = lineBreak(letterCount, tmp);
  }
  switch(tmp) {
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
  tmp = 0;
  return tmp;
}

int lineBreak(int letterCount, int tmp) {
  // if letter is at the end of the first line: jump
  if (letterCount == 17) {
    lcd.setCursor(0, 1);
  }
  // if letter is near the end of the first line: jump
  else if (letterCount >= 10 && letterCount <= 17 && tmp == 2222) {
    lcd.setCursor(0, 1);
    letterCount = 16;
  }
  // if a space is at the end of the second line: clear
  else if (letterCount == 33) {
    lcd.clear();
    letterCount = 0;
  }
  // if a space is near the end of the second line: clear
  else if (letterCount >= 28 && tmp == 2222) {
    letterCount = 0;
    lcd.clear(); 
  }
  return letterCount;
}
