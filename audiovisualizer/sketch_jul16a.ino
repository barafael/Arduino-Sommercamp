void setup(){
  Serial.begin(9600);
  Serial.setTimeout(1000);
}

enum State { UHR, SCHRITTE, KOERPER, DATUM, ENTFERNUNG,  };
State Zustand = UHR;


void loop(){
  long eingabe = Serial.parseInt();
  if(Zustand == UHR){
    Serial.println("Uhrzeit");
    if(eingabe==2){
      Zustand = 4;
    }
    if(eingabe == 1){
      Zustand = 2;
    }
  } 
  else if (Zustand == 2){
    Serial.println("Schritte");
    if(eingabe == 1){
      Zustand = 3; 
    }
    if(eingabe == 2){
      Zustand = 5;
    }
  }
  else if(Zustand == 3){
    Serial.println("Herzfrequenz");
    if(eingabe == 1){
      Zustand = 1;
    }
  }
  else if(Zustand == 4){
    Serial.println("Datum Zeigen");
    if(eingabe == 2){
      Zustand = 1;
    }
    if(eingabe == 1){
    Zustand = 2;
    }
  }
  else if(Zustand == 5){
    Serial.println("Entfernung Zeigen");
    if(eingabe == 2){
      Zustand = 2;
    }
    if(eingabe == 1){
      Zustand = 3;
    }
  }
  else if(Zustand == 6){
    Serial.println("Herzfrequenz");
    if(eingabe == 2){
      Zustand = 3;
    }
    if(eingabe == 1){
      Zustand = 1;
    }
  }

}

