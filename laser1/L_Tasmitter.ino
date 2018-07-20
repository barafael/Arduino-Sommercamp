#include <LiquidCrystal.h>

int laser = 10;
LiquidCrystal lcd(2, 3, 7, 6, 5, 4);
int intervall = 250;
char charToInt[27][2];

enum TransmissionState { START, SENDING, WAITING, END };

void setup() {
  /*for (int u = 0; u < 27; u++) {
    charToInt[u][1] = u + 1;
    }
    charToInt[0][0] = 'a';
    charToInt[1][0] = 'b';
    charToInt[2][0] = 'c';
    charToInt[3][0] = 'd';
    charToInt[4][0] = 'e';
    charToInt[5][0] = 'f';
    charToInt[6][0] = 'g';
    charToInt[7][0] = 'h';
    charToInt[8][0] = 'i';
    charToInt[9][0] = 'j';
    charToInt[10][0] = 'k';
    charToInt[11][0] = 'l';
    charToInt[12][0] = 'm';
    charToInt[13][0] = 'n';
    charToInt[14][0] = 'o';
    charToInt[15][0] = 'p';
    charToInt[16][0] = 'q';
    charToInt[17][0] = 'r';
    charToInt[18][0] = 's';
    charToInt[19][0] = 't';
    charToInt[20][0] = 'u';
    charToInt[21][0] = 'v';
    charToInt[22][0] = 'w';
    charToInt[23][0] = 'x';
    charToInt[24][0] = 'y';
    charToInt[25][0] = 'z';
    charToInt[26][0] = ' ';
  */
  Serial.begin(9600);
  pinMode(laser, OUTPUT);

  lcd.begin(16, 1);
}

int transmissionState = WAITING;

const int messageLength = 8;
int Message[messageLength];

void loop() {

  String textMessage = Serial.readString();
  if (textMessage != "") {
    char *textMessageToCharArray = new char[textMessage.length()];
    strcpy(textMessageToCharArray, textMessage.c_str());

    /*
      int IntInput[textMessage.length()];
      for (int g = 0; g < textMessage.length(); g++) {
      for (int h; h < 27; h++) {
        if (textMessageToCharArray[g] == charToInt[h][0]) {
          IntInput[g] = (int)charToInt[h][0];
        }
      }
      }*/
    transmissionState = START;
    for (int h = 0; h < textMessage.length(); h++) {
      Serial.println("H + " + h);
      Serial.println("TransmissionState" + transmissionState);

      for (int shiftValue = 0; shiftValue < messageLength - 3; shiftValue++) {
        char mask = 1 << shiftValue;
        boolean bitIsSet = mask & textMessageToCharArray[h];
        if (bitIsSet) {
          Message[shiftValue] = 1;
          Serial.println("Value 1" + Message[shiftValue]);

        } else {
          Message[shiftValue] = 0;
          Serial.println("Value 0" + Message[shiftValue]);
        }
      }

      delay(intervall);

      // Start of Transmission
      if (transmissionState == START) {
        lcd.print("Gestartet");
        digitalWrite(laser, HIGH);
         Serial.println(" Binär = 0");
        delay(intervall);
        digitalWrite(laser, LOW);
        delay(intervall); 
        digitalWrite(laser, HIGH);
        delay(intervall);
        digitalWrite(laser, LOW);
        delay(intervall);
         digitalWrite(laser, HIGH);
        delay(intervall);
        digitalWrite(laser, LOW);
        delay(intervall);
         digitalWrite(laser, HIGH);
        delay(intervall);
        digitalWrite(laser, LOW);
        delay(intervall);
         digitalWrite(laser, HIGH);
        delay(intervall);
        digitalWrite(laser, LOW);
        delay(intervall);
        transmissionState = SENDING;
        
        
        
        lcd.clear();
        lcd.print(textMessage);

      }

      // Transmission
      else if (transmissionState == SENDING) {
      }
      
      for (int i =  messageLength; i >= 0; i--) {
        if (Message[i] == 0) {
          digitalWrite(laser, LOW);
          delay(intervall/4);
          digitalWrite(laser, LOW);
          delay(intervall/4); 
          Serial.println(" Binär = 0");

          delay(intervall);
        } else if (Message[i] == 1) {
          digitalWrite(laser, HIGH);
          delay(intervall/4);
          Serial.println("Binär = 1");
        
          digitalWrite(laser, LOW);
            delay(intervall/4);
          
          
        }
      }
    }
    // Ends here
    digitalWrite(laser, HIGH);
        delay(intervall);
        digitalWrite(laser, LOW);
        delay(intervall); 
        digitalWrite(laser, LOW);
        delay(intervall);
        digitalWrite(laser, LOW);
        delay(intervall);
         digitalWrite(laser, HIGH);
        delay(intervall);
        digitalWrite(laser, LOW);
        delay(intervall);
         digitalWrite(laser, LOW);
        delay(intervall);
        digitalWrite(laser, LOW);
        delay(intervall);
        digitalWrite(laser, HIGH);
        delay(intervall);
        digitalWrite(laser, LOW);
        delay(intervall); 
        digitalWrite(laser, HIGH);
        delay(intervall);
        digitalWrite(laser, LOW);
        delay(intervall);
         digitalWrite(laser, HIGH);
        delay(intervall);
        digitalWrite(laser, LOW);
        delay(intervall);
         digitalWrite(laser, HIGH);
        delay(intervall);
        digitalWrite(laser, LOW);
        delay(intervall);
    lcd.print("Beendet");
    
    transmissionState = SENDING;
    delay(3000);
    lcd.clear();
  }

}

