    #include <SoftwareSerial.h>

    SoftwareSerial BLE_Serial(10, 11); // RX | TX

    void setup()

    {

    pinMode(9, OUTPUT); // this pin will pull the Module pin 34 (key pin) HIGH to switch module to AT mode

    digitalWrite(9, HIGH);

    Serial.begin(9600);

    Serial.println("Enter AT commands:");

    BLE_Serial.begin(38400); // Module default speed in AT command more

    }

    void loop()

    {

    // Keep reading from Module and send to Arduino Serial Monitor

    if (BLE_Serial.available())

    Serial.write(BLE_Serial.read());

    // Keep reading from Arduino Serial Monitor and send to Module

    if (Serial.available())

    BLE_Serial.write(Serial.read());

    }
