#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(3, 2); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);
void setup() {
  // put your setup code here, to run once:
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);

  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true);
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.volume(30);  //Set volume value. From 0 to 30
}

void loop() {
  // put your main code here, to run repeatedly:
 // playAudio(4);
 int noteValue[10]={10,30,510,420,140,70,1250,2330, 2000, 800};
 for (int x=0; x<10; x++){
  playFinalAudio(noteValue[x]);
 }
 
//  playFinalAudio(10);
//  playFinalAudio(30);
//  playFinalAudio(510);
//  playFinalAudio(420);
//  playFinalAudio(140);
//  playFinalAudio(70);
//  playFinalAudio(1250);
//  playFinalAudio(2335);
  
  if (myDFPlayer.available()) {
    printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
  }
}

int playFinalAudio(int number) {
  if (returnThousandsPlace(number) > 0) {
    playAudio(returnThousandsPlace(number));
    delay(1000);
    Serial.println(returnThousandsPlace(number));
    playAudio(1000);
    delay(1000);
    
  }

  if (returnHundredsPlace(number) > 0) {
    playAudio(returnHundredsPlace(number));
    delay(1000);
    Serial.println(returnHundredsPlace(number));
    playAudio(100);
    delay(1000);
  }

  if (returnTensPlace(number) > 0) {
    Serial.println(returnTensPlace(number));
    switch  (returnTensPlace(number)) {
      case 1:
        playAudio(10);
        break;
      case 2:
        playAudio(20);
        break;
      case 3:
        playAudio(30);
        break;
      case 4:
        playAudio(40);
        break;
      case 5:
        playAudio(50);
        break;
      case 6:
        playAudio(60);
        break;
      case 7:
        playAudio(70);
        break;
      case 8:
        playAudio(80);
        break;
      case 9:
        playAudio(90);
        break;
    }
    delay(1000);
  }
}

int returnThousandsPlace(int number) {

  int digit = number % 10000;
  digit = digit / 1000;
  return digit;

}


int returnHundredsPlace(int number) {

  int digit = number % 1000;
  digit = digit / 100;
  return digit;
}


int returnTensPlace(int number) {

  int digit = number % 100;
  digit = digit / 10;
  return digit;
}


void playAudio(int number) {
  switch  (number) {
    case 1:
      myDFPlayer.play(1);
      break;
    case 2 :
      myDFPlayer.play(2);
      break;
    case 3:
      myDFPlayer.play(3);
      break;
    case 4 :
      myDFPlayer.play(4);
      break;
    case 5:
      myDFPlayer.play(5);
      break;
    case 6 :
      myDFPlayer.play(6);
      break;
    case 7:
      myDFPlayer.play(7);
      break;
    case 8 :
      myDFPlayer.play(8);
      break;
    case 9:
      myDFPlayer.play(9);
      break;
    case 10 :
      myDFPlayer.play(10);
      break;
    case 20:
      myDFPlayer.play(11);
      break;
    case 30 :
      myDFPlayer.play(12);
      break;
    case 40:
      myDFPlayer.play(13);
      break;
    case 50 :
      myDFPlayer.play(14);
      break;
    case 60:
      myDFPlayer.play(15);
      break;
    case 70 :
      myDFPlayer.play(16);
      break;
    case 80:
      myDFPlayer.play(17);
      break;
    case 90 :
      myDFPlayer.play(18);
      break;
    case 100:
      myDFPlayer.play(19);
      break;
    case 1000 :
      myDFPlayer.play(20);
      break;

  }
}


void printDetail(uint8_t type, int value) {
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}
