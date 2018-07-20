enum Mode {SEND, READ};

int outPin = 10;
int last = millis();
int interval = 1000;
Mode mode = READ;

//sender
int max = 0;
int min = 10000;
String sender;
int charplace = 0;
int place = 0;
int startcounter = 8;

//reader
boolean calibrate = false;
int buffer[8] = {1, 1, 1, 1, 1, 1, 0, 1};
int start[8] = {0, 0, 0, 0, 0, 0, 1, 0};
boolean receiving = false;
int nthPlace = 0;

int startMillis;

void setup() {
  Serial.begin(9600);  
  pinMode(outPin, OUTPUT);
  digitalWrite(outPin, HIGH);
  pinMode(A1, INPUT);
}

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
      sender = "5Apfelkuchen";
      Serial.println(sender);
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
    if(mode == SEND && startcounter > 0) {
      if(startcounter == 2) {
        digitalWrite(outPin, HIGH);
        Serial.println("high");
      } else {
        digitalWrite(outPin, LOW);
        Serial.println("low");
      }
      startcounter--;
    } else if(mode == SEND && startcounter == 0) {
      int current = millis();
      if(current - last >= interval) {
        last = current;
        unsigned int first = sender.charAt(charplace);
        String binary = String(first, BIN);
        while(binary.length() < 8) {
          binary = "0" + binary;
        }
        if(place < sizeof(binary)) {
          if(binary.charAt(place) == '0') {
            digitalWrite(outPin, LOW);
            Serial.print("low - ");
            Serial.println(sender.charAt(charplace));
            place++;
          } else if(binary.charAt(place) == '1') {
            digitalWrite(outPin, HIGH);
            Serial.print("high - ");
            Serial.println(sender.charAt(charplace));
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
        int readValue;
        if(value > (min + max)/2) {
          readValue = 1;
          //Serial.print("min: ");Serial.println(min);
          //Serial.print("max: ");Serial.println(max);
        } else {
          readValue = 0;
          //Serial.print("min: ");Serial.println(min);
          //Serial.print("max: ");Serial.println(max);
        }
        Serial.println("Read: " + readValue);
        if(!receiving) {
          loopIt(readValue);
          if(buffer == start) {
            Serial.println("Let's get it started..huh");
            receiving = true;
          }
        } else {
          loopIt(readValue);
          nthPlace++;
          if(nthPlace = 8) {
            
          }
        } 
      } 
    } 
  }
}

void loopIt(int readValue) {
  for(int i = 0; i < 8; i++) {
    if(i == 7) {
      buffer[i] = readValue;
    } else {
      buffer[i] = buffer[i + 1];
    }
  }
}
