void setup() {
  Serial.begin(9600);
  pinMode(13, INPUT);
  digitalWrite(13, HIGH);
}

void loop() {
  boolean pressed = digitalRead(13) == LOW;
  if (pressed) {
    delay(200);
    Serial.println("Hello!");
  }
}
