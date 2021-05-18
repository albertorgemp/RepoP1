#include <Arduino.h>
#include "SD.h"
#include "SPI.h"

//  SPI PIN PORTS DEFINITIONS OF THE TEENSY 4.1 MODULE
#define CSt                         
#define SCKt
#define MOSIt
#define MISOt

//  SPI PIN PORTS DEFINITIONS OF THE AUDIO SHIELD MODULE
#define CSs                         
#define SCKs
#define MOSIs
#define MISOs


File root;

void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin()) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  root = SD.open("/");

  printDirectory(root, 0);

  Serial.println("done!");
}

void loop() {
  // nothing happens after setup finishes.
}




// void setup() {

//   Serial1.begin(115200);
//   // put your setup code here, to run once:e
 

// }

// void loop() {
 
//   Serial.println("Test");
//   delay(1000);
//   // put your main code here, to run repeatedly:
// }