#include <Wire.h>

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
}

void loop() {
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  
  int x = Wire.read(); // receive byte as an integer
  int y= Wire.read();
  Serial.println(x);         // print the integer
  Serial.println(y);         // print the integer
}
