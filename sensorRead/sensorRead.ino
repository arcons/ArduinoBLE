void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Right is Serial2
  //RX2 TX2
  Serial2.begin(9600);
  //Left is Serial3
  //RX3 TX3
  Serial3.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  readSensors()
}

void readSensors()
{
  if(Serial2.available())
  {
  
  }
  if(Serial2.available())
  {
  
  }
}

