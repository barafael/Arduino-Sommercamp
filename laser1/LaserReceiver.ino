enum Mode { INIT, DATA, TRANSEND };
// Change for Debug
int lightSensitivity = 30;

// Startzustand
int initalLight;
String msgBin ="";
String tempBin = "";

int isReceiving = 0;
int secSinceReceiveStart = 0;
int millisSinceLastState = 0;

int currState = 0;
int lastState = 0;

unsigned long ts = 0, tmeasure, tlast, tnext;
unsigned long t[5];

void setup(){
  Serial.begin(9600);
  initalLight = analogRead(A0);
  //String testmsg = buildMsg("110100000001011000110001111");
  //Serial.println(testmsg);
  t[4] = 0;
} 

Mode mode = INIT;

void loop(){
  
  //Serial.println(abs(currLight-initalLight));
  isReceiving = 1;
  t[0] = millis();

  // Receive-Mode
  if (mode == INIT){
    Serial.println("Init");
    int lastHasLight = 0;
    unsigned long lastSignalChangeTime = millis();
    int hasLight = 0;
    
    int z = 0; 
    while(z < 5) {
      int currLight = analogRead(A0);
      hasLight = currLight > lightSensitivity + initalLight;
      unsigned long lightTime = millis();
      
      int signalChange = lastHasLight != hasLight;
      lastHasLight = hasLight;      

      if (signalChange) {
        Serial.println("Signal change");
        t[z] = lightTime - lastSignalChangeTime;
        lastSignalChangeTime = lightTime;
        z++;
      }
    }

    long sum = 0;
    for(int i = 1;i<5;i++){
      sum = sum + t[i];
    }
    ts = (sum / 4);

    Serial.print("TS ");    
    Serial.print(ts);
    Serial.println();

    tlast = lastSignalChangeTime;
    tmeasure = tlast +(ts / 2);
    tnext = tlast + ts;
    mode = DATA;
  } else if(mode == DATA){
    if (millis() >= tmeasure) {
      
      int currLight = analogRead(A0);
      unsigned long lightTime = millis();
      int hasLight = abs(currLight-initalLight) > lightSensitivity;
      
      tlast = lightTime;
      tmeasure = tlast + (ts/2);
      tnext = tlast + ts;

      if (hasLight) {
        tempBin += "1";
      } else {
        tempBin += "0";
        Serial.println("Da kommt nen Ton");
      }
      
      if(tempBin.length()==9){
        Serial.println("Verschickt");
        buildMsg(tempBin);
        tempBin="";
      }

      Serial.println(tempBin);
      
    }

  }
}

char decodedLetter(String letterBin){

  char alphabet[27] = {
    'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',' ' };

  int letterDecimal = convertBinaryString(letterBin);
  char finalLetter = alphabet[letterDecimal-1];
  return finalLetter;

}

int convertBinaryString(String binString) {

  char *binChar = new char[binString.length()];
  strcpy(binChar, binString.c_str());
  Serial.println("Binary String"+binString);
  if(binChar[0]==1 || binChar[1]==1 || binChar[2]==1 ){
    Serial.println("Übertragung beendet");
    Serial.println("msgBin");
    mode = TRANSEND;
    return 0;
  }

  int result = 0;
  while(*binChar) {
    result <<= 1;
    if(*binChar++ == '1') result |= 1;
  }
  return result;
}

void buildMsg(String msg){
  /*
  char *tempChar = new char[msg.length()];
  strcpy(tempChar, msg.c_str());
  String finalMsg ="";

  for(int i=0;i<msg.length();i++){
    privatTempBin+=tempChar[i];
    if(i==(8*letterCount)-1){
      finalMsg+=decodedLetter(privatTempBin);

      letterCount++;
      privatTempBin="";
    }

  }
*/
  msgBin+=decodedLetter(msg);
  //Serial.println(decodedLetter(msgBin));
}







