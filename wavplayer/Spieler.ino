#include <TMRpcm.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>
#include <avr/wdt.h>

#define TFT_CS     10
#define TFT_RST    3
#define TFT_DC     8

int sensorPin = A0;
int ledPin = 9;
int sensorValue = 0;

TMRpcm tmrpcm;
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

File root;
int fileNum = 0;
int menuDelay = 200;
const int kardinality = 15;
int pointer = 1;
String fileList[(kardinality + 1)];

File fileToOpen;
int actorNum = 0;
int playTime = 0;
int counter = 0;
int startTime = 0;

void setup() {
  tmrpcm.speakerPin = 9;
  tmrpcm.setVolume(7);
  Serial.begin(9600);
  while (!Serial) {}
  tft.initR(INITR_144GREENTAB);
  tft.fillScreen(ST77XX_BLACK);

  if (!SD.begin(4)) { testdrawtext("NO SD!", ST77XX_RED); while (1); }
  
  root = SD.open("/");
  
  uint16_t time = millis();
  time = millis() - time;
  tft.fillScreen(ST77XX_BLACK);
  
  printDirectory(root);
  
  while (true) {
  
  counter = 0;
  
    while (true) {
      if (counter == (kardinality + 1)) { break; }
      if (counter == 0) {} else { 
        if (counter == pointer) {
          tft.setCursor(10, counter * 10);
          tft.setTextColor(ST77XX_GREEN);
          tft.setTextWrap(true);
          tft.print(fileList[counter]); 
        } else {
          tft.setCursor(10, counter * 10);
          tft.setTextColor(ST77XX_WHITE);
          tft.setTextWrap(true);
          tft.print(fileList[counter]); 
        }
      }
      counter++;}
      
    //L (runter)
    if (buttoninput() == 1) {
      delay(menuDelay);
      if (pointer == (fileNum - 1)) {
        pointer = 1;
      } else {
        pointer++;
      }
    }
    
    //E (auswaehlen)
    if (buttoninput() == 2) {
      
      if (fileList[pointer].charAt(fileList[pointer].length()-1) == 'V') {
        Serial.print("Playing Music: ");
        char actor[50];
        fileList[pointer].toCharArray(actor, (fileList[pointer].length()+1));
        fileToOpen = SD.open(actor); 
        actorNum = pointer;
        playTime = fileToOpen.size() / 8000;
          
          Serial.print("Playing ");
          Serial.print(actor);
          Serial.print(" with the size ");
          Serial.print(fileToOpen.size());
          Serial.print(" Bytes and with the time ");
          Serial.print(playTime);
          Serial.print(" Seconds");
          Serial.print('!');
          Serial.print('\n');
          
            counter = 0;
  
            while (true) {
              if (counter == (kardinality + 1)) { break; }
              if (counter == 0) {} else { 
                if (counter == pointer) {
                  tft.setCursor(10, counter * 10);
                  tft.setTextColor(ST77XX_BLUE);
                  tft.setTextWrap(true);
                  tft.print(fileList[counter]); 
                } else {
                  tft.setCursor(10, counter * 10);
                  tft.setTextColor(ST77XX_WHITE);
                  tft.setTextWrap(true);
                  tft.print(fileList[counter]); 
                }
              }
              counter++;}
          
        fileToOpen.close();
        
        tmrpcm.play(actor);
        //startTime = millis();
        
        delay(menuDelay);
        // while (startTime + (playTime * 1000) >= millis()) {
        while (true) {
          
              if ((buttoninput() == 1) || (buttoninput() == 4)) {
                      tmrpcm.stopPlayback();
                      tmrpcm.disable();
                      break;}
                      
              if ((buttoninput() == 2)) {
                      tmrpcm.pause();
                      delay(menuDelay);}
        }
 
        tmrpcm.stopPlayback();
        tmrpcm.disable();
        
        Serial.println("ENDE\n");
        
        
      } else if (fileList[pointer].charAt(fileList[pointer].length()-1) == 'P') { 
        Serial.print("Showing Picture: ");
        char actor[50];
        fileList[pointer].toCharArray(actor, (fileList[pointer].length()+1));
        tft.fillScreen(ST77XX_BLACK);
        bmpDraw(actor, 0, 0);
        delay(500);
        while (buttoninput() == 0) {}
        softwareReset();
      }
    }
    
    //R (hoch)
    if (buttoninput() == 4) {
      delay(menuDelay);
      if (pointer == 1) {
        pointer = (fileNum - 1);
      } else {
        pointer--;
      }
    }
    
    //Abbruch
    if (buttoninput() == 5) {
      
    }
  }

}

void loop() {
  // nothing happens...
}

int buttoninput() {
  
  int button1 = 0; 
  int button2 = 0;
  int button3 = 0;
  int delaytime = 0;
  int output = 0;
  
  if (analogRead(A0) > 400) { 
     delay(delaytime);
     button1 = 1;
  }
  
  if (analogRead(A1) > 400) { 
     delay(delaytime);
     button2 = 1;
  }
  
  if (analogRead(A2) > 400) { 
     delay(delaytime);
     button3 = 1;
  }
  
  output = 1 * button1 + 2 * button2 + 4 * button3;
  return output;
  
}

void printDirectory(File dir) {
  int counter = 0;
  fileNum = 0;
  while (true) {  

    File entry = dir.openNextFile();
    if (! entry) { break; }
    if (counter == (kardinality + 1)) { break; }
    
    fileList[counter] = entry.name();
    counter++;
    fileNum++;
    entry.close();
  }
}

#define BUFFPIXEL 20

void bmpDraw(char *filename, uint8_t x, uint16_t y) {

  File     bmpFile;
  int      bmpWidth, bmpHeight;
  uint8_t  bmpDepth;
  uint32_t bmpImageoffset;
  uint32_t rowSize;
  uint8_t  sdbuffer[3*BUFFPIXEL]; 
  uint8_t  buffidx = sizeof(sdbuffer); 
  boolean  goodBmp = false;       
  boolean  flip    = true;        
  int      w, h, row, col;
  uint8_t  r, g, b;
  uint32_t pos = 0, startTime = millis();

  if((x >= tft.width()) || (y >= tft.height())) return;

  Serial.println();
  Serial.print(F("Loading image '"));
  Serial.print(filename);
  Serial.println('\'');
  
  if ((bmpFile = SD.open(filename)) == NULL) {
    Serial.print(F("File not found"));
    return;}
    
  if(read16(bmpFile) == 0x4D42) {
    Serial.print(F("File size: ")); Serial.println(read32(bmpFile));
    (void)read32(bmpFile);
    bmpImageoffset = read32(bmpFile);
    Serial.print(F("Image Offset: ")); Serial.println(bmpImageoffset, DEC);
    Serial.print(F("Header size: ")); Serial.println(read32(bmpFile));
    bmpWidth  = read32(bmpFile);
    bmpHeight = read32(bmpFile);
    if(read16(bmpFile) == 1) {
      bmpDepth = read16(bmpFile);
      Serial.print(F("Bit Depth: ")); Serial.println(bmpDepth);
      if((bmpDepth == 24) && (read32(bmpFile) == 0)) {

        goodBmp = true;
        Serial.print(F("Image size: "));
        Serial.print(bmpWidth);
        Serial.print('x');
        Serial.println(bmpHeight);
        
        rowSize = (bmpWidth * 3 + 3) & ~3;

        if(bmpHeight < 0) {
          bmpHeight = -bmpHeight;
          flip      = false;
        }

        w = bmpWidth;
        h = bmpHeight;
        if((x+w-1) >= tft.width())  w = tft.width()  - x;
        if((y+h-1) >= tft.height()) h = tft.height() - y;
        tft.setAddrWindow(x, y, x+w-1, y+h-1);

        for (row=0; row<h; row++) { 
          if(flip)
            pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
          else
            pos = bmpImageoffset + row * rowSize;
          if(bmpFile.position() != pos) {
            bmpFile.seek(pos);
            buffidx = sizeof(sdbuffer);
          }

          for (col=0; col<w; col++) {
            if (buffidx >= sizeof(sdbuffer)) {
              bmpFile.read(sdbuffer, sizeof(sdbuffer));
              buffidx = 0;
            }

            b = sdbuffer[buffidx++];
            g = sdbuffer[buffidx++];
            r = sdbuffer[buffidx++];
            tft.pushColor(tft.color565(r,g,b));
          }
        }
        Serial.print(F("Loaded in "));
        Serial.print(millis() - startTime);
        Serial.println(" ms");
      }
    }
  }

  bmpFile.close();
  if(!goodBmp) Serial.println(F("BMP format not recognized."));
}

uint16_t read16(File f) {
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read();
  ((uint8_t *)&result)[1] = f.read();
  return result;
}

uint32_t read32(File f) {
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read();
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read();
  return result;
} void softwareReset() { wdt_enable(WDTO_60MS); while(1) {} }



void testdrawtext(char *text, uint16_t color) {
  tft.setCursor(10, 10);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}
