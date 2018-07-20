enum State { UHR,SCHRITTE, KOERPER };
State zustand=UHR;
int nebenZustand=1;
void setup(){
  Serial.begin(9600);
  Serial.setTimeout(1000);
}
int nebenZustandAendern(long e){
  if(e==1){
    if(nebenZustand==1){
      return 2;
    }
    else{
      return 1;
    }
  }
}
void loop(){
  long eingabe = Serial.parseInt();
  long eingabe2 = Serial.parseInt();
  if (zustand==UHR){
    if(nebenZustand==1){
       Serial.println("Uhrzeit");
    }
    else{
      Serial.println("Datum");
    }
    if(eingabe==1){
      zustand==SCHRITTE;
    }
    nebenZustand=nebenZustandAendern(eingabe2);
    
  }
  else if(zustand==SCHRITTE){
    if(nebenZustand==1){
       Serial.println("Schritte");
    }
    else{
      Serial.println("Entfernung");
    }
    if(eingabe==1){
      zustand==KOERPER;
    }
    nebenZustand=nebenZustandAendern(eingabe2);
  }
  else if(zustand==KOERPER){
    if(nebenZustand==1){
       Serial.println("Herzfrequenz");
    }
    else{
      Serial.println("Kalorienverbrauch");
    }
    if(eingabe==1){
      zustand==UHR;
    }
    nebenZustand=nebenZustandAendern(eingabe2);
  }
}
  
