int sensorPin = A0;
int ledPin = 9;
int sensorValue = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);  
}

void loop() {
  if (buttoninput() == 2) { 
    playsound(440, 9);
  }
}

void playsound(int f, int speakerpin) {
  float t = (1.0 / f) * 1000;
  Serial.println(t);
  digitalWrite(ledPin, HIGH);  
  delay(t);             
  digitalWrite(ledPin, LOW);   
  delay(t);
}

int buttoninput() {
  
  int button1 = 0; 
  int button2 = 0;
  int button3 = 0;
  int delaytime = 0;
  int output = 0;
  
  if (analogRead(A0) > 400) { 
     delay(delaytime);
     button1 = 1;
  }
  
  if (analogRead(A1) > 400) { 
     delay(delaytime);
     button2 = 1;
  }
  
  if (analogRead(A2) > 400) { 
     delay(delaytime);
     button3 = 1;
  }
  
  output = 1 * button1 + 2 * button2 + 4 * button3;
  Serial.print("Buttons = {");
  Serial.print(button1);
  Serial.print(button2);
  Serial.print(button3);
  Serial.print("} = ");
  Serial.print(output);
  Serial.print('\n');
  
  return output;
  
}
