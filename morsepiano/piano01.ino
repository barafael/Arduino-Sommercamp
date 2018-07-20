// tone in hertz
const int C = 261.63;
const int D = 293.67;
const int E = 329.63;
const int F = 349.23;
const int G = 392.00;
const int A = 440.00;
const int H = 493.88;
const int C2 = 523.25;

const int BUZZER_PIN = 4;

void setup() {
  // Buzzer
  pinMode(BUZZER_PIN, OUTPUT);
  
  // C
  pinMode(12, INPUT);
  digitalWrite(12, HIGH);
  // D
  pinMode(11, INPUT);
  digitalWrite(11, HIGH);
  // E
  pinMode(10, INPUT);
  digitalWrite(10, HIGH);
  // F
  pinMode(9, INPUT);
  digitalWrite(9, HIGH);
  // G
  pinMode(8, INPUT);
  digitalWrite(8, HIGH);
  // A
  pinMode(7, INPUT);
  digitalWrite(7, HIGH);
  // H
  pinMode(6, INPUT);
  digitalWrite(6, HIGH);
  // C2
  pinMode(5, INPUT);
  digitalWrite(5, HIGH);
}

void loop() {
  boolean PressC = digitalRead(12) == LOW;
  boolean PressD = digitalRead(11) == LOW;
  boolean PressE = digitalRead(10) == LOW;
  boolean PressF = digitalRead(9) == LOW;
  boolean PressG = digitalRead(8) == LOW;
  boolean PressA = digitalRead(7) == LOW;
  boolean PressH = digitalRead(6) == LOW;
  boolean PressC2 = digitalRead(5) == LOW;
  
  int timePressed = 25;
  if (PressC) {
    tone(BUZZER_PIN, C, timePressed);
  } else if (PressD) {
    tone(BUZZER_PIN, D, timePressed);
  } else if (PressE) {
    tone(BUZZER_PIN, E, timePressed);
  } else if (PressF) {
    tone(BUZZER_PIN, F, timePressed);
  } else if (PressG) {
    tone(BUZZER_PIN, G, timePressed);
  } else if (PressA) {
    tone(BUZZER_PIN, A, timePressed);
  } else if (PressH) {
    tone(BUZZER_PIN, H, timePressed);
  } else if (PressC2) {
    tone(BUZZER_PIN, C2, timePressed);
  }
}
