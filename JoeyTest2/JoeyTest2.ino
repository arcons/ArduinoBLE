
void setup() {
  // put your setup code here, to run once:
  //Start both serials
  Serial.begin(9600);
  //Joeys output is serial 1
  Serial1.begin(9600);
  //Set a 500ms timeout
  Serial1.setTimeout(10);
  char test = 0x0A;
}

void loop() {
  byte joeyInput[10];
  byte bufferNum=0x00;
  if(Serial1.available())
  {
    bufferNum = Serial1.readBytes(joeyInput, 10);
    //Serial.write(joeyInput, 10);
//    Serial.write(joeyInput[4]);
//    Serial.write(joeyInput[5]);
//    Serial.write(joeyInput[6]);
//    Serial.write(joeyInput[7]);
  
    byte arrhythmia = joeyInput[4];
    byte heartRate = joeyInput[5];
//    Serial.print(arrhythmia, DEC);
//    Serial.print(heartRate, DEC);
    byte amplitudeLSB = joeyInput[6];
    byte amplitudeMSB = joeyInput[7];
//    Serial.print(amplitudeLSB, DEC);
//    Serial.print(amplitudeMSB, DEC);
    int iamplitude = ((amplitudeMSB << 8) & 0xFF00) | (amplitudeLSB & 0x00FF);
    Serial.println(iamplitude);
  }
    //byte mainValues[4] = {arrhythmia, heartRate, amplitudeMSB, amplitudeLSB};// joeyInput[8], joeyInput[9]};
    //Serial.write(mainValues,4);
//
//    int iArrhythmia = (int)arrhythmia;
//    int iHeartRate = (int)heartRate;
//    int iamplitude = ((amplitudeMSB << 8) & 0xFF00) | (amplitudeLSB & 0x00FF);
//    //Serial.write(joeyInput,4);
//    Serial.print(" Arrhythmia is : ");
//    Serial.print(iArrhythmia);
//    Serial.print(" Heart rate is : ");
//    Serial.print(iHeartRate);
//    Serial.print(" Amplitude is : ");
//    Serial.print(iamplitude);
//    Serial.println("");
//    }
//    Serial.println(" ");
    
//    Serial.write(joeyInput,10);
//  if (Serial1.available()) 
//  {
//    Serial.write(Serial1.read());
//  }
//  if(Serial.available())
//  {
//    Serial1.write(Serial.read());
//  }

}
