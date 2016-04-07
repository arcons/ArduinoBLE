


// inslude the SPI library:
#include <SPI.h>


byte sinewave[256] ={
 127,130,133,136,139,143,146,149,152,155,158,161,164,167,170,173,176,178,181,184,187,190,192,195,198,200,203,205,208,210,212,215,217,219,221,223,225,227,229,231,233,234,236,238,239,240,
 242,243,244,245,247,248,249,249,250,251,252,252,253,253,253,254,254,254,254,254,254,254,253,253,253,252,252,251,250,249,249,248,247,245,244,243,242,240,239,238,236,234,233,231,229,227,225,223,
 221,219,217,215,212,210,208,205,203,200,198,195,192,190,187,184,181,178,176,173,170,167,164,161,158,155,152,149,146,143,139,136,133,130,127,124,121,118,115,111,108,105,102,99,96,93,90,87,84,81,78,
 76,73,70,67,64,62,59,56,54,51,49,46,44,42,39,37,35,33,31,29,27,25,23,21,20,18,16,15,14,12,11,10,9,7,6,5,5,4,3,2,2,1,1,1,0,0,0,0,0,0,0,1,1,1,2,2,3,4,5,5,6,7,9,10,11,12,14,15,16,18,20,21,23,25,27,29,31,
 33,35,37,39,42,44,46,49,51,54,56,59,62,64,67,70,73,76,78,81,84,87,90,93,96,99,102,105,108,111,115,118,121,124

};
//long int sinewave[256] ={
//32768,33572,34375,35178,35979,36779,37575,38369,
//39160,39947,40729,41507,42279,43046,43807,44560,
//45307,46046,46777,47500,48214,48919,49613,50298,
//50972,51635,52287,52927,53555,54170,54773,55362,
//55938,56499,57047,57579,58097,58600,59087,59558,
//60013,60451,60873,61278,61666,62036,62389,62724,
//63041,63339,63620,63881,64124,64348,64553,64739,
//64905,65053,65180,65289,65377,65446,65496,65525,
//65535,65525,65496,65446,65377,65289,65180,65053,
//64905,64739,64553,64348,64124,63881,63620,63339,
//63041,62724,62389,62036,61666,61278,60873,60451,
//60013,59558,59087,58600,58097,57579,57047,56499,
//55938,55362,54773,54170,53555,52927,52287,51635,
//50972,50298,49613,48919,48214,47500,46777,46046,
//45307,44560,43807,43046,42279,41507,40729,39947,
//39160,38369,37575,36779,35979,35178,34375,33572,
//32768,31963,31160,30357,29556,28756,27960,27166,
//26375,25588,24806,24028,23256,22489,21728,20975,
//20228,19489,18758,18035,17321,16616,15922,15237,
//14563,13900,13248,12608,11980,11365,10762,10173,
//9597,9036,8488,7956,7438,6935,6448,5977,
//5522,5084,4662,4257,3869,3499,3146,2811,
//2494,2196,1915,1654,1411,1187,982,796,
//630,482,355,246,158,89,39,10,
//0,10,39,89,158,246,355,482,
//630,796,982,1187,1411,1654,1915,2196,
//2494,2811,3146,3499,3869,4257,4662,5084,
//5522,5977,6448,6935,7438,7956,8488,9036,
//9597,10173,10762,11365,11980,12608,13248,13900,
//14563,15237,15922,16616,17321,18035,18758,19489,
//20228,20975,21728,22489,23256,24028,24806,25588,
//26375,27166,27960,28756,29556,30357,31160,31963,
//};

#define DATAOUT 51   // MOSI 
#define DATAIN 50    // MISO //not used
#define SPICLOCK 52  // Clock 
#define SELPIN 53    // chip-select
void setup() {

  // set the slaveSelectPin as an output:
  digitalWrite(SELPIN, HIGH); 
  pinMode(SELPIN, OUTPUT);
  pinMode(SPICLOCK, OUTPUT);
  pinMode(DATAOUT, OUTPUT);
  // initialize SPI:
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV16); // slow the SPI bus down
  Serial.begin(115200);
}

void loop() {
  // go through the six channels of the digital pot:
  for (int channel = 0; channel < 256; channel++) {
    // change the resistance on this channel from min to max:
    writeSPI(sinewave[channel]);
    // wait a second at the top:
    delay(50);
  }

}

void writeSPI( byte value){ // I previously thought the DAC had multiple outputs (channels), it only has one
// and the mode control bits are inserted into the bit stream.  I was wrong on how to send the data stream.

// configure SPI hardware for the maximum clock rate, bit order, clock phase and polarity

  SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE1)); // set correct SPI modes

  // take the SS pin low to select the chip:

  digitalWrite(SELPIN, LOW);


  //  send device Mode bits and the first 6bits of the DAC value via SPI:

  byte output = value >>2; // the high bits b7, b6 need to be 0 for normal mode
 
  // send the control bits plus the high 6 bits of the output value
 
  SPI.transfer(output);

  output = value << 6; //  get the rest of the input value, the lower 2 bits of value, pad with zero's

  SPI.transfer(output);
  
  output = 0;
  // Send a filler byte, the device expects 24 bits of data
  SPI.transfer(output);

  // take the SS pin high to de-select the chip:
  digitalWrite(SELPIN, HIGH);
  SPI.endTransaction(); // release SPI bus for other devices
  
}
//void writeSPI(long int value){ // I previously thought the DAC had multiple outputs (channels), it only has one
//// and the mode control bits are inserted into the bit stream.  I was wrong on how to send the data stream.
//
//// configure SPI hardware for the maximum clock rate, bit order, clock phase and polarity
//
//  SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0)); // set correct SPI modes
//
//  // take the SS pin low to select the chip:
//
//  digitalWrite(SELPIN, LOW);
//
//  //  send device Mode bits and the first 6bits of the DAC value via SPI:
//
//  int16_t output = value >> 2; // the high bits b7, b6 need to be 0 for normal mode
// 
//  // send the control bits plus the high 6 bits of the output value
// 
//  SPI.transfer16(output);
//
//  output = value; //  get the rest of the input value, the lower 2 bits of value, pad with zero's
//
//  
//  output = 0;
//  // Send a filler byte, the device expects 24 bits of data
//  SPI.transfer16(output);
//
//  // take the SS pin high to de-select the chip:
//  digitalWrite(SELPIN, HIGH);
//  SPI.endTransaction(); // release SPI bus for other devices
//  
//}
