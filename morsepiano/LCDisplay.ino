#include<LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 7, 6, 5, 4);

void setup() {
  lcd.begin(16, 2);
  lcd.print("Hallo");
}

void loop() {
  lcd.setCursor(0, 1);
}
