void setup() {
  Serial.begin(9600);
  pinMode(11, INPUT);
  digitalWrite(11, HIGH);
  pinMode(12, INPUT);
  digitalWrite(12, HIGH);
  pinMode(13, INPUT);
  digitalWrite(13, HIGH);
}

void loop() {
  boolean pressed1 = digitalRead(11) == LOW;
  boolean pressed2 = digitalRead(12) == LOW;
  boolean pressed3 = digitalRead(13) == LOW;
  if (pressed1) {
    delay(200);
    Serial.println("Hallo");
  }
  else if (pressed2) {
    delay(200);
    Serial.println("Welt");
  }
  else if (pressed3) {
    delay(200);
    Serial.println("!");
  }
}
