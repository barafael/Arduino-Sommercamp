
#include <dht.h>

dht DHT;

#define DHT11_PIN 7
int SensorPin = A5;
int Sensorwert;
float sensorschnitt;
const int buzzer = 8;

void setup() {
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
}

void loop()
{
   int chk = DHT.read11(DHT11_PIN);
    Serial.print("Temperature = ");
    Serial.println(DHT.temperature);
    Serial.print("Humidity = ");
    Serial.println(DHT.humidity);
    delay(1000);
  

  Sensorwert = analogRead(SensorPin);
  sensorschnitt = MAF_next(Sensorwert);
  delay(10);
  //Serial.println(sensorschnitt);

  if (Spitze(sensorschnitt)) {
    //Serial.println("Beep");
    tone(buzzer, 5000); // Send 1KHz sound signal...
    delay(10);        // ...for 1 sec
    noTone(buzzer);
    Serial.println(rBPM());
}



    /* tone(buzzer, 1000); // Send 1KHz sound signal...
      delay(10);        // ...for 1 sec
    
  */
}

int marker = 0;
const int MAF_SIZE = 16;

float values[MAF_SIZE];


//MAF heißt Moving average auf Deutsch für doofe: gleitendes Mittel

float MAF_next(float value) {
  marker++;
  if (marker >= MAF_SIZE) {
    marker = 0;
  }
  values[marker] = value;
  float sum = 0;
  for (int index = 0; index < MAF_SIZE; index++) {
    sum += values[index];
  }
  return sum / MAF_SIZE;
}


const int SIZE = 15;
int mar=0;
float val[SIZE];

int rBPM(){
  
  mar++;
  if (mar >= SIZE) {
    mar = 0;
  }
  val[mar] = BPM();
  float sum = 0;
  for (int index = 0; index < SIZE; index++) {
    sum += val[index];
  }
  return sum / SIZE;
  
}

const int ANZAHL_WERTE = 25;
int mark = 1;
int Werte[ANZAHL_WERTE];
int erst = 0;


int BPM () {

  if (mark >= ANZAHL_WERTE) {
    mark = 0;
  }
  Werte[mark] = millis();

  if (erst >= ANZAHL_WERTE) {
    erst = 0;
  }

  int f =   Werte[mark] - Werte[erst];
  mark++;
  erst++;


  return (6000.0 / (f / (float)(ANZAHL_WERTE - 1)));
}

float vglWert;
int vgmarker;
int vgsteigend;
int steigend;
int i;

int Spitze (int sensorschnitt) {
  if (vglWert > sensorschnitt) {
    steigend = 0;
  } else if (vglWert <= sensorschnitt) {
    steigend = 1;
  }

  if (vgsteigend > steigend) {
    if (sensorschnitt > vgmarker)
    {
      i = true;
    } else {
      i = false;
    }

    vgmarker = sensorschnitt + 100;
  }
  else {
    i = false;
  }
  vglWert = sensorschnitt;
  vgsteigend = steigend;

  return i;
}


