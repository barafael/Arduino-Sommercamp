int x=1;
int y=1;
long gesamtzeit=0;
void setup() { 
  Serial.begin(9600);  
}

void loop() {
  gesamtzeit=millis();

  if(gesamtzeit>x*33) {
    x++;
  }
  if(gesamtzeit>y*250){
    y++;
    Serial.println(x-1);
  }
}
