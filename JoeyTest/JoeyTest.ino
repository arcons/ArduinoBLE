/*
  Software serial multple serial test

 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.

 The circuit:
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)

 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts,
 so only the following can be used for RX:
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

 Not all pins on the Leonardo support change interrupts,
 so only the following can be used for RX:
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).

 created back in the mists of time
 modified 25 May 2012
 by Tom Igoe
 based on Mikal Hart's example

 This example code is in the public domain.

 */
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX
int counter=0;
byte messageStart[4] = {'a', 'b', 'c', 'd'};
byte input[4];
byte arrythmia = 0x08;
byte heartRate = 0x07;
byte amplitudeLSB = 0x0A;
byte amplitudeMSB = 0x0B;
byte dspOutput[12];
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("Hello, world?");
}

void loop()
{ // run over and over
  if (mySerial.available())
  {
    bool packetEnd = false;
      input[0] = mySerial.read();
      if(input[0]=='a')
      {
        Serial.println("a");
        input[1] = mySerial.read();
        if(input[1]==0x62)
        {
          Serial.println("b");
          input[2] = mySerial.read();
          if(input[2]==0x63)
          {
            Serial.println("c");
            input[3] = mySerial.read();
            if(input[3]==0x64)
            {
            Serial.println("HOLY FUCK IT STARTED RIGHT BUT THIS CODE IS SHIT");
            arrythmia = mySerial.read();
            heartRate = mySerial.read();
            amplitudeLSB = mySerial.read();
            amplitudeMSB = mySerial.read();
            }
          }
        }
      }
      else
      {
        packetEnd = true;
        //Serial.println("Unsucessful start bits");
      }
    }
//    if(counter<12)
//    {
//      byte input = mySerial.read();
//      if(counter<5 && messageStart[counter] == input)
//      {
//        Serial.println("Start packets");
//      }
//      else if(counter==6)
//      {
//        packetNum = input;
//      }
//      else if(counter==7)
//      {
//        heartRate = input;
//      }
//      else if(counter==8)
//      {
//        arrythmia = input;
//      }
//      else if(counter==10)
//      {
//        amplitudeLSB = input;
//      }
//      else if(counter==11)
//      {
//        amplitudeLSB = input;
//      }
//      counter++;
//    }
//    else
//    {
//      Serial.print("Packet Number: ");
//      Serial.println((int)packetNum);
//      Serial.print("Heart Rate: ");
//      Serial.println((int)heartRate);
//      Serial.print("Arryhthmia: ");
//      Serial.println((int)arrythmia);
//      Serial.print("Amplitude: ");
//      Serial.println((int)amplitudeMSB);
//      
//      counter=0;
//    }
//    Serial.write(mySerial.read());
//    Serial.print("Joey's output is ");
//    Serial.println(output);
//  if (Serial.available()) {
//    mySerial.write(Serial.read());
//  }
delay(5);
}

void fourByteRead()
{
      input[0] = mySerial.read();
      input[1] = mySerial.read();
      input[2] = mySerial.read();
      input[3] = mySerial.read();
}

bool packetStart(byte *input)
{
    int comp=0;
    int i =0;
    for(i=0; i<4; i++)
    {
      if(input[i] == messageStart[i])
      {
        comp++;
      }
    }
    if(comp==4)
    {
      return true;
    }
    else
    {
      return false;
    }
}
