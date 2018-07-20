
#include <Manchester.h>

int initalLight;
String msgBin ="";


void setup(){

    Serial.begin(9600);
    initalLight = analogRead(A0);
    
} 


int isReceiving = 0;
int secSinceReceiveStart = 1;
int receiveStartTime;



void loop(){


 int currLight = analogRead(A0);
 //Serial.println(abs(currLight-initalLight));
 
 if(abs(currLight-initalLight) > 53 && isReceiving==0){
 
   //Start Receiving
   isReceiving = 1;
   Serial.println("Übertragung gestartet");
   //ToDo Synchronität
   
   while(abs(currLight-initalLight) > 53){
     currLight = analogRead(A0);
   }
   receiveStartTime = millis();
   
   
 }

  //Receive-Mode
 if(isReceiving==1){
 
   if(millis() > receiveStartTime+500*secSinceReceiveStart){
   
     if(abs(currLight-initalLight) > 40){
     
       Serial.println("Licht aus");
       msgBin+="0";
       
     }else
     if(abs(currLight-initalLight) < 40){
     
       Serial.println("Licht an");
       msgBin+="1";
     }
     secSinceReceiveStart++;
   
   }
 
 
 } 

}

