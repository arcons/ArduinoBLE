#include <Wire.h>
#include <Adafruit_MCP4725.h>


short heartTestData[255] =
{
0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254
};

Adafruit_MCP4725 dacLeft;
Adafruit_MCP4725 dacRight;
byte mHasArrhythmia=0x00;
byte mAmplitude[2];
byte mHeartRate=0x00;

byte output[4];

uint16_t i=0;

void setup(){
  //Use Serial for Karson
  //This is temporarily set to view the output
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

  //Begin Connection
  Serial2.print("AT+START");
  Serial3.print("AT+START");
  delay(100);
  Serial2.print("go");
  Serial3.print("go");

  //Right is DAC
  dacLeft.begin(0x62);
  //Right is DAC2 this has A0 jumped to VDD for the 0x63 address
  dacRight.begin(0x63);

}

void loop()
{

  byte rightInput[4];
  byte leftInput[4];
  byte joeyInput[4];
  //Test the outpouts
  //Read the outputs from bluetooh
  if(Serial2.available())
  {
    //Remove later, read the bytes and output them to view via realterm
    Serial.write(Serial2.readBytes(rightInput, 4));
    //Store in the buffer
  }
  if(Serial3.available())
  {
    //Remove later, read the bytes and output them to view via realterm
    Serial.write(Serial3.readBytes(leftInput, 4));
    //Store in the buffer
  }

  //Scale the voltage down from 16 bits to 12 bits
  uint16_t leftVoltage = leftInput[3]*256 + leftInput[4];
  uint16_t rightVoltage = rightInput[3]*256 + rightInput[4];

  leftVoltage = leftVoltage/4;
  rightVoltage = rightVoltage/4;

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

