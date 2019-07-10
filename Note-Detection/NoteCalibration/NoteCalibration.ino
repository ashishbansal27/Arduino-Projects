#include <Array.h>
const int arraysize = 20;
int readingr[arraysize];
int readingb[arraysize];
int readingg[arraysize];
int readingcount;
int readingDelay=50;
int averageb;
int averager;
int averageg;

#define S0 4
#define S1 5
#define S2 6
#define S3 8
#define sensorOut 9

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  pinMode(sensorOut, INPUT);
  // Setting frequency scaling to 2%
  digitalWrite(S0, LOW);
  digitalWrite(S1, HIGH);
  pinMode(A0, INPUT);

  // Begins serial communication
  Serial.begin(9600);
}

void loop() {


  if (digitalRead(A0)) {

    for (readingcount = 0; readingcount < arraysize; readingcount++)
    {
      readingr[readingcount] = getreadingr();
      readingb[readingcount] = getreadingb();
      readingg[readingcount] = getreadingg();
      delay(readingDelay);
    }



    Array<int> array = Array<int>(readingr, arraysize);
    averager = array.getAverage();


    Array<int> array1 = Array<int>(readingb, arraysize);
    averageb = array1.getAverage();

    Array<int>array2 = Array<int>(readingg, arraysize);
    averageg = array2.getAverage();


    //Serial.print("average red is . ");
    Serial.print(averager);

    //Serial.print(" .  average blue is . ");
    Serial.print(",");
    Serial.print(averageb);

   // Serial.print(" . average green is . ");
    Serial.print(",");
    Serial.println(averageg);
    while(digitalRead(A0)){}

    int noteValue= whatNote(averager,averageb,averageg);
//    Serial.print("Note is: ");
//    Serial.println(noteValue);
    
  }

  



}

int getreadingr() {

  // Setting RED (R) filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);

  // Reading the output frequency
  int redFrequency = pulseIn(sensorOut, LOW);
  return redFrequency;



}

int getreadingb() {

  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);

  // Reading the output frequency
  int blueFrequency = pulseIn(sensorOut, LOW);
  return blueFrequency;
}


int getreadingg() {


  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  int greenFrequency = pulseIn(sensorOut, LOW);
  return greenFrequency;

}

int whatNote(int averageR, int averageB, int averageG){
  if(((averageR>740)&&(averageR<930))&&((averageB>840)&&(averageB<1040))&&((averageG>860)&&(averageG<1070))){
    return 500;
  }
  else if(((averageR>470)&&(averageR<550))&&((averageB>780)&&(averageB<970))&&((averageG>760)&&(averageG<890))){
    return 200;
  }
  else return 0;
}




