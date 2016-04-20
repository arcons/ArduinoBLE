#include <SoftwareSerial.h>

//hook these up properly you fool
SoftwareSerial BTSerial(11, 10); //RX|TX

void setup(){
  Serial.begin(9600);
  BTSerial.begin(9600); // default baud rate
  //Serial.begin(9600);
  //BTSerial.begin(57600); // default baud rate
  while(!Serial); //if it is an Arduino Micro
  Serial.println("AT commands: ");
    digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);    
}

void loop(){
  //read from the HM-10 and print in the Serial
  if(BTSerial.available())
  {
    Serial.write(BTSerial.read());
  }
    
  //read from the Serial and print to the HM-10
  if(Serial.available())
    {
      BTSerial.write(Serial.read());
    }
  //  BTSerial.write(Serial.read());

}
