
#include <SPI.h>
#include <SD.h>

File root;
const int kardinality = 15;
String fileList[(kardinality + 1)];

void setup() {

  Serial.begin(9600);
  while (!Serial) {}


  if (!SD.begin(4)) { printme("NO SD!", 1); while (1); }
  
  root = SD.open("/");
  
  printDirectory(root);

}

void loop() {
  // nothing happens after setup finishes.
}

void printDirectory(File dir) {
  int counter = 0;
  while (true) {

    File entry = dir.openNextFile();
    if (! entry) { break; }
    if (counter == (kardinality + 1)) { break; }
    
    fileList[counter] = entry.name();
    if (counter == 0) {} else { printme(fileList[counter], 1); }
    counter++;
    entry.close();
  }
}

void printme(String input, String marker) {
  
}
