#include <MFRC522.h>
#include "Keyboard.h"
#include <SPI.h>

#define SAD 10
#define RST 3
int tagID=0;

MFRC522 nfc(SAD, RST);

void setup() {
  Serial.begin(115200);
  Keyboard.begin();
  Serial.println("can you see me ?");
  SPI.begin();
  // Read a fast as possible. There is a limit for how long we are
  // allowed to read from the tags.
  

  Serial.println("Looking for MFRC522.");
  nfc.begin();

  // Get the firmware version of the RFID chip
  byte version = nfc.getFirmwareVersion();
  if (! version) {
    Serial.print("Didn't find MFRC522 board.");
    while(1); //halt
  }

  Serial.print("Found chip MFRC522 ");
  Serial.print("Firmware ver. 0x");
  Serial.print(version, HEX);
  Serial.println(".");
}

byte keyA[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, };
byte keyB[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, };

void loop() {
  byte status;
  byte data[MAX_LEN];
  byte serial[5];
  serial[0]=0;
  int i, j, pos;

  // Send a general request out into the aether. If there is a tag in
  // the area it will respond and the status will be MI_OK.
  status = nfc.requestTag(MF1_REQIDL, data);

  if (status == MI_OK) {
    Serial.println("Tag detected.");
    Serial.print("Type: ");
    Serial.print(data[0], HEX);
    Serial.print(", ");
    Serial.println(data[1], HEX);

    // calculate the anti-collision value for the currently detected
    // tag and write the serial into the data array.
    status = nfc.antiCollision(data);
    memcpy(serial, data, 5);

    Serial.println("The serial nb of the tag is:");
    for (i = 0; i < 3; i++) {
      Serial.print(serial[i]);
      Serial.print(", ");
    }
    Serial.println(serial[3]);

    // Select the tag that we want to talk to. If we don't do this the
    // chip does not know which tag it should talk if there should be
    // any other tags in the area..
    nfc.selectTag(serial);

    

    // Stop the tag and get ready for reading a new tag.
    //nfc.haltTag();
  }
  delay(100);

  tagID=serial[0];
  Serial.println(tagID);

//  while (tagID!=180||tagID!=109||tagID!=178||tagID!=194) {
//    // do nothing until pin 2 goes low
//    delay(500);
//  }

  switch (tagID) {
    
    case 180:
       Keyboard.print((1));
       Keyboard.print(0);
      delay(100);
      //Keyboard.release((1));
//      Keyboard.press(0);
//      delay(100);
//      Keyboard.release(0);
      Keyboard.press('\n');
      delay(100); 
      Keyboard.releaseAll();
      
      
      break;
      
    case 109:
      Keyboard.press("2");
      delay(100);
      Keyboard.release("2");
      Keyboard.press('0');
      delay(100);
      Keyboard.release('0');
      Keyboard.press('\n');
      delay(100);
      Keyboard.releaseAll();
      //tagID=0;
      
      break;
      
    case 178:
     
     Keyboard.press('3');
      delay(100);
      Keyboard.release('3');
      Keyboard.press('0');
      delay(100);
      Keyboard.release('0');
      Keyboard.press('\n');
      delay(100);
      Keyboard.releaseAll();
      //tagID=0;
      
      break;

       case 194:

       Keyboard.press('4');
      delay(100);
      Keyboard.release('4');
      Keyboard.press('0');
      delay(100);
      Keyboard.release('0');
      Keyboard.press('\n');
      delay(100);
      Keyboard.releaseAll();
      //tagID=0;
      
      break;
  }
  tagID=0;
  serial[0]=0;
  nfc.haltTag();
}
