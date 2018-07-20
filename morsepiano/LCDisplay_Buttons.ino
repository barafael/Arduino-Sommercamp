#include<LiquidCrystal.h>
void setup() {
  LiquidCrystal lcd(2, 3, 7, 6, 5, 4);
  lcd.begin(16, 2);
  lcd.print("Hallo Welt!");
  
  pinMode(11, INPUT);
  digitalWrite(11, HIGH);
  pinMode(12, INPUT);
  digitalWrite(12, HIGH);
  pinMode(13, INPUT);
  digitalWrite(13, HIGH);
}

void loop() {
  boolean pressed1 = digitalRead(11) == LOW;
  boolean pressed2 = digitalRead(12) == LOW;
  boolean pressed3 = digitalRead(13) == LOW;
  if (pressed1) {
    delay(200);
    lcd.print("Hallo");
  }
  else if (pressed2) {
    delay(200);
    lcd.print("Welt");
  }
  else if (pressed3) {
    delay(200);
    lcd.print("!");
  }
}
