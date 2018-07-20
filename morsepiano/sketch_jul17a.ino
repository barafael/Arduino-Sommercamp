
int rot=10;
int gelb=9;
int gruen=8;
int blau=7;
int Trot=6;
int Tgelb=5;
int Tgruen=4;
int Tblau=3;

void lost(){
 digitalWrite(10,HIGH);
        digitalWrite(9,HIGH);
        digitalWrite(8,HIGH);
        digitalWrite(7,HIGH);
        delay(3000);
        digitalWrite(10,LOW);
        digitalWrite(9,LOW);
        digitalWrite(8,LOW);
        digitalWrite(7,LOW);
        
       
}


void setup(){
  // Farbe der LED.
  pinMode(rot,OUTPUT);
  pinMode(gelb,OUTPUT);
  pinMode(gruen,OUTPUT);
  pinMode(blau,OUTPUT);

  // Taster, die jeweils zu den LED gehoeren.
  pinMode(Trot,INPUT);
  pinMode(Tgelb,INPUT);
  pinMode(Tgruen,INPUT);
  pinMode(Tblau,INPUT);
  
  digitalWrite(Trot,HIGH);
  digitalWrite(Tgelb,HIGH);
  digitalWrite(Tgruen,HIGH);
  digitalWrite(Tblau,HIGH);
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

const int runden = 10; 

void loop(){
  Serial.println("Das Spiel beginnt!");

  for(int h=0;h<runden;h++){
    delay(1000);
    Serial.print("Runde Nummer ");
    Serial.println(h+1);

    // Speichert alle Zufallszahlen ab, um später die Eingänge überprüfen zu können.
    int zahlenfeld[runden][h+4];
    for(int i = 0; i<h+4; i++){
      int zufallsZahl=random(1,5);

      // Weist der zufällig generierten zahl einen Eingang zu.
      int ledPin=zufallsZahl+6;
      zahlenfeld[h][i]=ledPin;

      // Schaltet eine zufällig ausgewählte LED für eine Sekunde an und dann wieder aus, dieser Vorgang wird h+4 mal durchgeführt wobei h die Runde ist in der man sich befindet (Z33), diese Folge von LED muss sich der Spieler merken.
      Serial.print(zahlenfeld[h][i]);
      int pin = zahlenfeld[h][i];
      digitalWrite(pin,HIGH);
      delay(1000);
      digitalWrite(pin,LOW);
      delay(1000);
    }

    for (int k=0; k<h+4; k++){

      // Notwendig, da die Eingangsnummern der Taster um 4 höher sind als die, der Lampen für die sie verantwortlich sind.
      int TEingabe = zahlenfeld[h][k] - 4;
      Serial.println("Achtung, jetzt bitte Eingeben");
      delay(2000/(h+1));
      
      // Bei gedrueckter Taste wird der Zustand "LOW" ausgelesen, bei nicht gedrueckter Taste der Zustand "HIGH".
      boolean gedrueckt = digitalRead (TEingabe) == HIGH;
      Serial.println(gedrueckt);
      if(gedrueckt){
        lost();
         Serial.print("Leider falsch, Highscore:");
        Serial.println(h);
        delay(30000); 
        return;
      }
      else{
        digitalWrite(TEingabe+4,HIGH);
        delay(1000);
        digitalWrite(TEingabe+4,LOW);
        
      }
    }
  }
}





