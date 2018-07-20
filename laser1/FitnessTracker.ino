
void setup(){
  Serial.begin(9600);
  Serial.setTimeout(1000);

}

enum State {UHR, SCHRITTE, KOERPER};

int uhrZustand = 1;
int schrittZustand = 1;
int herzZustand = 1;

State zustand = UHR;

void loop(){

  long eingabe = Serial.parseInt();
  
  if(zustand == UHR){
    if(uhrZustand == 1){
      Serial.println("Uhrzeit");
      if (eingabe == 2) {
        uhrZustand = 2;
      }
    }else 
    if(uhrZustand == 2){
      Serial.println("Datum");
      if (eingabe == 2) {
        uhrZustand = 1;
      }
    }
    if (eingabe == 1) {
      zustand = SCHRITTE;
    }
    
    
  }else if(zustand == SCHRITTE){
    if(schrittZustand == 1){
      Serial.println("Schritte");
      if (eingabe == 2) {
        schrittZustand = 2;
      }
    }else 
    if(schrittZustand == 2){
      Serial.println("Distanz");
      if (eingabe == 2) {
        uhrZustand = 1;
      }
    }
    if (eingabe == 1) {
      zustand = KOERPER;
    }
    
    
  }else if(zustand == KOERPER){
    if(herzZustand == 1){
      Serial.println("Herzfrequenz");
      if (eingabe == 2) {
        herzZustand = 2;
      }
    }else 
    if(herzZustand == 2){
      Serial.println("Kalorienverbrauch");
      if (eingabe == 2) {
        herzZustand = 1;
      }
    }
    if (eingabe == 1) {
      zustand = SCHRITTE; 
    }
    
    
  }
 

}
