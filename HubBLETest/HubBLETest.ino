#include <Wire.h>
#include <Adafruit_MCP4725.h>
#include <SoftwareSerial.h>

SoftwareSerial RightSerial(11,10);
 
 Adafruit_MCP4725 dacRight;
 bool connectionStatus=false;
 char goMessage[2] = {'g', 'o'};
 byte rightInput[6];
 uint16_t rightVoltage;
 uint16_t counter=0;
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial2.begin(9600);
  delay(100);

  //Start the write address(Jumper from A0 to VDD)
  dacRight.begin(0x62);
  Serial2.print("go");
  Serial2.write(0x00);
}

void loop() {
  // put your main code here, to run repeatedly:
    //Serial2.print("go");
    //Input should be no larger than twenty bytes since thats however many that can sent via BLE
    memset(rightInput,0,sizeof(rightInput));  
//    //output the hex values
//    Serial.print(Serial.read(), HEX);
   if(Serial2.available()>=6)
   {
//    rightInput[0] = RightSerial.read();
//    rightInput[1] = RightSerial.read();
//    rightInput[2] = RightSerial.read();
//    rightInput[3] = RightSerial.read();
//    rightInput[4] = RightSerial.read();
//    rightInput[5] = RightSerial.read();
      Serial2.readBytes(rightInput,6);
      Serial2.write(0x00);
//    if(rightInput[0] == 0xFF && rightInput[3] == 0xFF)
//    {
      rightVoltage = rightInput[2]*256 + rightInput[3];
      dacRight.setVoltage(rightVoltage, false);
      Serial.print(rightInput[0], DEC);
      Serial.print(rightInput[1], DEC);
      Serial.print(rightInput[2], DEC);
      Serial.print(rightInput[3], DEC);
      Serial.print(rightInput[4], DEC);
      Serial.println(rightInput[5], DEC);
//      Serial.println(rightInput[3], HEX);
//      Serial.println(rightVoltage);
//    }
//    Serial.print(rightInput[0], HEX);
//    Serial.print(rightInput[3], HEX);
//    Serial.println("");
//    Serial.write(rightInput,6);
   }
//   else
//      Serial2.flush();
//      Serial2.readBytes(rightInput, 4);
//    Serial2.readBytes(rightInput,20);
//    Serial.write(rightInput,20);
//    uint16_t rightVoltage = rightInput[11]*256 + rightInput[12];
//    rightVoltage = rightVoltage/4;
//    Should be close to 4096 for AIN=GND
//    Serial.print("First byte ");
//    Serial.print(rightInput[0], HEX);
//    Serial.print("\tSecond byte ");
//    Serial.print(rightInput[11], HEX);
//    Serial.print("\tThird byte ");
//    Serial.print(rightInput[12], HEX);
//    Serial.print("\tFourth byte ");
//    Serial.print(rightInput[3], HEX);
//    Serial.print("\t");
//      rightVoltage = rightVoltage/16;
//      Serial.print(rightVoltage);
//    if(Serial2.available()>2)
//    {
//    if(rightInput[0] == (uint8_t)255 && rightInput[3] == (uint8_t)255)
//    {
//      Serial.println("K");
//    }
//    Serial.println("");
//    Serial.print("First byte ");
//    Serial.write(rightInput[0]);
//    Serial.println("");
//    Serial.print("Second byte ");
//    Serial.write(rightInput[1]);
//    Serial.println("");
//    Serial.print("Third byte ");
//    Serial.write(rightInput[2]);
//    Serial.println("");
//    Serial.print("Fourth byte ");
//    Serial.write(rightInput[3]);
//    Serial.print(Serial2.available());
//    Serial.print("\t");
//    Serial2.readBytes(rightInput,2);
//    }
//    else{
//    rightInput[0]=Serial2.read();
//    }
//      Serial.println(Serial2.read());
//    Serial.println(rightInput[0]);
    //rightVoltage = rightVoltage/16;
//    Serial.print("The output from the ADC is ");
    //This section would be the normal output to Karson;
    //Serial.println(rightVoltage);
      //Store in the buffer
//    dacRight.setVoltage(rightVoltage, false);
//    Serial.println("All bytes have been read");
}
