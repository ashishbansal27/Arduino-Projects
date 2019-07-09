#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <MFRC522.h>
#include "Keyboard.h"
#include <SPI.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
#define SAD 3
#define RST 2
int tagID=0;

MFRC522 nfc(SAD, RST);

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5
//T=tence place, U = unit place, Add= address
int tag1TAdd=0;
int tag1UAdd=1;
int tag2TAdd=2;
int tag2UAdd=3;
int tag3TAdd=4;
int tag3UAdd=5;
int tag4TAdd=6;
int tag4UAdd=7;
int count =0;
 //U= unit , T= Tence , Val = value
int tag1TVal = EEPROM.read(tag1TAdd);
int tag1UVal= EEPROM.read(tag1UAdd);
int tag2TVal = EEPROM.read(tag2TAdd);
int tag2UVal= EEPROM.read(tag2UAdd);
int tag3TVal = EEPROM.read(tag3TAdd);
int tag3UVal= EEPROM.read(tag3UAdd);
int tag4TVal = EEPROM.read(tag4TAdd);
int tag4UVal= EEPROM.read(tag4UAdd);

void setup() {

  Keyboard.begin();
  Serial.println("can you see me ?");
  SPI.begin();
  // Read a fast as possible. There is a limit for how long we are
  // allowed to read from the tags.
  Serial.begin(115200);

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
  // put your setup code here, to run once:
 lcd.begin(16, 2);
  Serial.begin(9600);
  lcd.setCursor(5, 0);
  lcd.print("trial");
  lcd.blink();
  delay(1000);
  
  

  
}

void loop() {

  if (count==0){
  
  lcd.setCursor(0, 0);
  lcd.print("Tag 1 Ten's");
  lcd.setCursor(0,1);
  lcd.print(tag1TVal);
  
  
  // put your main code here, to run repeatedly:
if (getLCDButton()== btnUP){
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print(tag1TVal);
  tag1TVal++;
  if (tag1TVal>9){
    tag1TVal=0;
  }
  while(getLCDButton()== btnUP);
}

if (getLCDButton()==btnSELECT){
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print("Saved");
  delay(200);
  lcd.blink();
  EEPROM.update(tag1TAdd,tag1TVal);
  count++;
}


  }


    if (count==1){
  
  lcd.setCursor(0, 0);
  lcd.print("Tag 1 Unit's");
  lcd.setCursor(0,1);
  lcd.print(tag1UVal);
  
if (getLCDButton()== btnUP){
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print(tag1UVal);
  tag1UVal++;
  if (tag1UVal>9){
    tag1UVal=0;
  }
  while(getLCDButton()== btnUP);
}

if (getLCDButton()==btnSELECT){
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print("Saved");
  delay(200);
  lcd.blink();
  EEPROM.update(tag1UAdd,tag1UVal);
  count++;
}


  }


    if (count==2){
  
  lcd.setCursor(0, 0);
  lcd.print("Tag 2 Ten's");
  lcd.setCursor(0,1);
  lcd.print(tag2TVal);
  
  
  // put your main code here, to run repeatedly:
if (getLCDButton()== btnUP){
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print(tag2TVal);
  tag2TVal++;
  if (tag2TVal>9){
    tag2TVal=0;
  }
  while(getLCDButton()== btnUP);
}

if (getLCDButton()==btnSELECT){
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print("Saved");
  delay(200);
  lcd.blink();
  EEPROM.update(tag2TAdd,tag2TVal);
  count++;
}
    }

  if (count==3){
  
  lcd.setCursor(0, 0);
  lcd.print("Tag 2 Unit's");
  lcd.setCursor(0,1);
  lcd.print(tag2UVal);
  
  
  // put your main code here, to run repeatedly:
if (getLCDButton()== btnUP){
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print(tag2UVal);
  tag2UVal++;
  if (tag2UVal>9){
    tag2UVal=0;
  }
  while(getLCDButton()== btnUP);
}

if (getLCDButton()==btnSELECT){
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print("Saved");
  delay(200);
  lcd.blink();
  EEPROM.update(tag2UAdd,tag2UVal);
  count++;
}


  }

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
  //Serial.println(tagID);

//  while (tagID!=180||tagID!=109||tagID!=178||tagID!=194) {
//    // do nothing until pin 2 goes low
//    delay(500);
//  }

  switch (tagID) {
    
    case 180:
   
      Keyboard.print(tag1TVal);
      Keyboard.print(tag1UVal);
      Keyboard.press('\n');
      delay(100); 
      Keyboard.releaseAll();
      
      
      break;
      
    case 178:
      Keyboard.print(tag2TVal);
      Keyboard.print(tag2UVal);
      Keyboard.press('\n');
      delay(100);
      Keyboard.releaseAll();
      //tagID=0;
      
      break;
      
    case 109:
     
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

int getLCDButton() {
  int adc_key_in = analogRead(0);

  /*
     The button values are centered on:
     0000 - right
     0100 - up
     0256 - down
     0410 - left
     0640 - select
     1023 - none
  */

  if (adc_key_in > 1000) return btnNONE;
  if (adc_key_in < 50)   return btnRIGHT;
  if (adc_key_in < 195)  return btnUP;
  if (adc_key_in < 380)  return btnDOWN;
  if (adc_key_in < 555)  return btnLEFT;
  if (adc_key_in < 790)  return btnSELECT;

  return btnNONE;
}
