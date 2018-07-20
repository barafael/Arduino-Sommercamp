
int currTime;
int outputTime;
int incrementTime;

int counter = 0;

void setup() {

  Serial.begin(9600);  
  outputTime = millis();
  incrementTime = outputTime;

}

void loop(){

  currTime = millis();
  
  if(currTime-incrementTime >= 33){
    counter = counter+1;
    incrementTime = millis();
  }
  
  if(currTime-outputTime >= 250){
    Serial.println(counter);
    outputTime = millis();
  }
  
}

