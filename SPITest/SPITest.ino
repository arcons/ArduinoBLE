/*
  Digital Pot Control

  This example controls an Analog Devices AD5206 digital potentiometer.
  The AD5206 has 6 potentiometer channels. Each channel's pins are labeled
  A - connect this to voltage
  W - this is the pot's wiper, which changes when you set it
  B - connect this to ground.

 The AD5206 is SPI-compatible,and to command it, you send two bytes,
 one with the channel number (0 - 5) and one with the resistance value for the
 channel (0 - 255).

 The circuit:
  * All A pins  of AD5206 connected to +5V
  * All B pins of AD5206 connected to ground
  * An LED and a 220-ohm resisor in series connected from each W pin to ground
  * CS - to digital pin 10  (SS pin)
  * SDI - to digital pin 11 (MOSI pin)
  * CLK - to digital pin 13 (SCK pin)

 created 10 Aug 2010
 by Tom Igoe

 Thanks to Heather Dewey-Hagborg for the original tutorial, 2005

*/


// inslude the SPI library:
#include <SPI.h>

float sinewave[66] = {0.43725,0.397125,0.4918125,0.59625,0.5724375,0.4516875,0.39375,0.475125,0.5881875,0.5836875,0.467625,0.3931875,0.458625,0.5775,0.5934375,0.4850625,0.3954375,0.4426875,0.5645625,0.6,0.5019375,0.4005,0.4291875,0.5503125,0.6039375,0.5188125,0.407625,0.4175625,0.5353125,0.60525,0.5349375,0.4171875,0.4078125,0.5191875,0.604125,0.5503125,0.4288125,0.4005,0.5026875,0.6,0.564375,0.4426875,0.3954375,0.48525,0.59325,0.577125,0.457875,0.3931875,0.4689375,0.584625,0.58725,0.4734375,0.3935625,0.4531875,0.573375,0.595875,0.4906875,0.3969375,0.4381875,0.5600625,0.6015,0.507375,0.4025625,0.4250625,0.5454375,0.6046875};
// set pin 10 as the slave select for the digital pot:

#define SELPIN 53    // chip-select
#define DATAOUT 51   // MOSI 
#define DATAIN 50    // MISO 
#define SPICLOCK 52  // Clock 

void setup() {
  // set the slaveSelectPin as an output:
  pinMode(SELPIN, OUTPUT);
  // initialize SPI:
  digitalWrite(SELPIN, HIGH); 
  
  SPI.setClockDivider( SPI_CLOCK_DIV16 ); // slow the SPI bus down
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);    // SPI 0,0 as per MCP330x data sheet 
  SPI.begin();
  Serial.begin(115200);
}

void loop() {
  // go through the six channels of the digital pot:
  for (int channel = 0; channel < 66; channel++) {
    // change the resistance on this channel from min to max:
    writeSPI(sinewave[channel]);
    // wait a second at the top:
    delay(100);
  }

}

void writeSPI(float value) {
  // take the SS pin low to select the chip:
  digitalWrite(SELPIN, LOW);
  //  send in the address and value via SPI:
  int output = value/0.1875 * 1000 *5;
  SPI.transfer(output);
  Serial.print(output);
  // take the SS pin high to de-select the chip:
  digitalWrite(SELPIN, HIGH);
}
