

void setup() {
  Serial.begin(9600);
  
}

void loop() {
  Serial.println(digitalRead(KNOPF_LESER));
  while(digitalRead(KNOPF_LESER) == HIGH){
    analogWrite(LED, 255);
    delay(100);
    
    
    
  }
  for(int i = 255; i> 0; i--){
      analogWrite(LED, i);
      delay(3);
    }
  while(digitalRead(KNOPF_LESER) == LOW){
    
    
    analogWrite(LED, 0);
  }
}
