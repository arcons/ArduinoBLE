#include <Wire.h>
#include <Adafruit_MCP4725.h>
#include <SoftwareSerial.h>

SoftwareSerial KarsonSerial(11, 10); //RX|TX


short heartTestData[255] =
{
0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254
};

<<<<<<< HEAD
Adafruit_MCP4725 dacLeft;
Adafruit_MCP4725 dacRight;
=======
>>>>>>> origin/master
byte mHasArrhythmia=0x00;
byte mAmplitude[2];
byte mHeartRate=0x00;

byte output[4];

uint16_t i=0;

void setup(){
<<<<<<< HEAD
  //Use Serial for Karson
=======
  //Output the data received via usb serial
>>>>>>> origin/master
  Serial.begin(9600);
  //DSP is Serial1
  //RX1 TX1
  Serial1.begin(9600);
  //Right is Serial2
  //RX2 TX2
  Serial2.begin(9600);
  //Left is Serial3
  //RX3 TX3
  Serial3.begin(9600);
<<<<<<< HEAD

  //Begin Connection
  Serial2.print("AT+START");
  Serial3.print("AT+START");
  Serial2.print("go");
  Serial3.print("go");
=======
  //Use software serial for Karson
  KarsonSerial.begin(9600); // default baud rate
>>>>>>> origin/master
}

void loop(){
  //read from the HM-10 and print in the Serial
  if(i==255)
  {
    i=0;
  }
  if(JoeySerial.available())
  {
    Serial.write(JoeySerial.read());
  }

  
  Serial.println(testData[i]);
  int temp = testData[i];
  temp &= 0xFF;
  mAmplitudeLSB[0] = testData[i]>>8 & 0xFF;
  mAmplitudeMSB[1] = temp;

 int heartrate = heartTestData[i]; //random(255);
 int arryth = 1;
  output[3] = (byte)heartrate; //heart rate
  output[2] = mAmplitudeMSB[1];
  output[1] = mAmplitudeLSB[0];
  output[0] = (byte)arryth;  //arryhthmia
  //Serial.write(output, 5);
  KarsonSerial.write(output,5);
  i++;
  delay(20);
}

void outputToKarson(byte dspInput[4])
{
<<<<<<< HEAD
=======
  byte output[4]={dspInput[0], dspInput[1], dspInput[2], dspInput[3]};
>>>>>>> origin/master

  byte rightInput[4];
  byte leftInput[4];
  byte joeyInput[4];
  //Test the outpouts
  if(Serial2.available())
  {
    Serial.write(Serial2.readBytes(rightInput, 4));
    //Store in the buffer
  }
  if(Serial3.available())
  {
    Serial.write(Serial3.readBytes(leftInput, 4));
    //Store in the buffer
  }

  //Scale the voltage down from 16 bits to 12 bits
  uint16_t leftVoltage = leftInput[3]*256 + leftInput[4];
  uint16_t rightVoltage = rightInput[3]*256 + rightInput[4];;

  Serial.print("The right voltage is:");
  Serial.println(rightVoltage);
  
  dacLeft.setVoltage(leftVoltage, false);
  dacRight.setVoltage(rightVoltage, false);

 //Check for data availibilty from joey
 if(Serial1.available())
 {
   Serial1.readBytes(joeyInput, 4);
   //Write To Karson
   Serial.write(joeyInput,4);
 }
}
<<<<<<< HEAD
=======
}
>>>>>>> origin/master

