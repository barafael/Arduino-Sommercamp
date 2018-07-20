enum Mode {SEND, READ};

int outPin = 10;
int last = millis();
int interval = 1000;
int max = 0;
int min = 10000;
boolean calibrate = false;
String sender;
int charplace = 0;
int place = 0;

int startMillis;

void setup() {
  Serial.begin(9600);  
  pinMode(outPin, OUTPUT);
  digitalWrite(outPin, HIGH);
  pinMode(A1, INPUT);
}

Mode mode = READ;

void loop() {
  if(Serial.available() > 0) {
    String input = Serial.readString();
    if(input == "read") {
      mode = READ;
      digitalWrite(outPin, HIGH);
    } else if(input == "send") {
      mode = SEND;
      charplace = 0;
      place = 0;
      sender = "Apfelkuchen";
    } else if(input == "calibrate") {
      calibrate = true;
      max = 0;
      min = 10000;
    } else if(input == "stopCali") {
      calibrate = false;
    } else if(input != "") {
      Serial.println("wrong command");
    }
  } else {
    if(mode == SEND) {
      int current = millis();
      if(current - last >= interval) {
        last = current;
        unsigned int first = sender.charAt(charplace);
        Serial.println(first);
        String binary = String(first, BIN);
        Serial.println("bin: " + String(binary.charAt(place)));
        if(place < sizeof(binary)) {
          if(binary.charAt(place) == '0') {
            digitalWrite(outPin, LOW);
            Serial.println("low");
            place++;
          } else if(binary.charAt(place) == '1') {
            digitalWrite(outPin, HIGH);
            Serial.println("high");
            place++;
          }
        } else {
          charplace++;
          place = 0;
        }
        
      } 
    } else if(mode == READ) {
      int value = analogRead(A1);
      if(calibrate) {
        if(value > max) {
          max = value;
        } else if(value < min) {
          min = value;
        }
      }
      int current = millis();
      if(current - last >= interval) {
        last = current;
        if(value > (min + max)/2) {
          Serial.println(1);
          //Serial.print("min: ");Serial.println(min);
          //Serial.print("max: ");Serial.println(max);
        } else {
          Serial.println(0);
          //Serial.print("min: ");Serial.println(min);
          //Serial.print("max: ");Serial.println(max);
        }
      } 
    } 
  } 
}


