void setup() {
  Serial.begin(9600);
  Serial.setTimeout(1000);
}

int zustand = 1;

void loop() {
  long eingabe = Serial.parseInt();
  if (zustand == 1) {
    Serial.println("Uhrzeit");
    if (eingabe == 1) {
      zustand = 2;
    }
    else if (eingabe==2){
      zustand = 4;
    }
  }
  else if (zustand == 2) {
    Serial.println("Schritte");
    if (eingabe == 1) {
      zustand = 3;
    }
    else if (eingabe==2){
      zustand = 5;
    }
  }
  else if (zustand == 3) {
    Serial.println("Herzfrequenz");
    if (eingabe == 1) {
      zustand = 1;
    }
    else if (eingabe==2){
      zustand = 6;
    }
  }
  else if (zustand == 4) {
    Serial.println("Datum");
    if (eingabe == 1) {
      zustand = 2;
    }
    else if (eingabe==2){
      zustand = 1;
    }
  }
  else if (zustand == 5) {
    Serial.println("Entfernung");
    if (eingabe == 1) {
      zustand = 3;
    }
    else if (eingabe==2){
      zustand = 2;
    }
  }
  else if (zustand == 6) {
    Serial.println("Kalorienverbrauch");
    if (eingabe == 1) {
      zustand = 1;
    }
    else if (eingabe==2){
      zustand = 3;
    }
  }
}
  
