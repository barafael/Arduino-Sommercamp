const int PIN_LEFT  = 5;
const int PIN_DOWN  = 4;
const int PIN_UP    = 3;
const int PIN_RIGHT = 2;

void setup() {
    Serial.begin(9600);
    pinMode(PIN_LEFT,  INPUT);
    pinMode(PIN_DOWN,  INPUT);
    pinMode(PIN_UP,    INPUT);
    pinMode(PIN_RIGHT, INPUT);

    // Pullup-Widerstand aktivieren
    digitalWrite(PIN_LEFT,  HIGH);
    digitalWrite(PIN_DOWN,  HIGH);
    digitalWrite(PIN_UP,    HIGH);
    digitalWrite(PIN_RIGHT, HIGH);
}

void loop() {
    bool pressedLeft  = digitalRead(PIN_LEFT)  == LOW;
    bool pressedDown  = digitalRead(PIN_DOWN)  == LOW;
    bool pressedUp    = digitalRead(PIN_UP)    == LOW;
    bool pressedRight = digitalRead(PIN_RIGHT) == LOW;

    if (pressedLeft) {
        Serial.println("Nach links");
    } else if (pressedDown) {
        Serial.println("Nach unten");
    } else if (pressedUp) {
        Serial.println("Nach oben");
    } else if (pressedRight) {
        Serial.println("Nach rechts");
    }

    delay(100);
}
