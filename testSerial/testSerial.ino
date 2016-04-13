void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial2.begin(9600);
  Serial.println("AT commands: ");
}

void loop() {
  // put your main code here, to run repeatedly:
 if (Serial.available())
 {
   Serial.read();
 }
//  if (Serial2.available())
// {
//   Serial2.read();
// }
 delay(100);
}
