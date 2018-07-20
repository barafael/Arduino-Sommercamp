
int initalLight;
int initalLight2;

int lightSensitivity = 40;


void setup(){
  Serial.begin(9600);
  pinMode(3,OUTPUT);
  pinMode(10,OUTPUT);
  
  initalLight = analogRead(A0);
  initalLight = analogRead(A1);
  
  
}

void loop(){
  digitalWrite(10,HIGH);
  int currLight = analogRead(A0);
  int currLight2 = analogRead(A1);
  //Serial.println(abs(currLight-initalLight));
  
   if(abs(currLight-initalLight) > 40)
   {
   
     Serial.println("Da kommt ein Ton");
     tone(3,18000,2);
   }
   if(abs(currLight2-initalLight2) > 40)
   {
   
     Serial.println("Da kommt ein Ton");
     tone(3,6000,2);
   }

}
