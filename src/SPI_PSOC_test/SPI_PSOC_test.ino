// MOSI: pin 11 P3[0]
// MISO: pin 12   P3[1]
// SCK: pin 13 P0[6]
// the sensor communicates using SPI, so include the library:
#include <SPI.h>
#include <Wire.h>

// pins used for the connection with the sensor
// the other you need are controlled by the SPI library):
const int chipSelectPin = 10; //P0[7]

unsigned long color;

void setup() {
  while(!Serial);
  //delay(1000);

  Wire.begin();
  Serial.begin(9200);

  color = 1u;

  // start the SPI library:
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV32);
  SPI.begin();
  //digitalWrite(SS, HIGH);  // ensure SS stays high

  pinMode(chipSelectPin, OUTPUT);

  // give the sensor time to set up:
  //delay(100);
}

void loop() {
  sendData(color);
  
  color = color + 1u;

  if(color > 3u){
    color = 0u;
  }
  
  
 
  delay(100);
}


//Sends a write command to SCP1000

void sendData(unsigned long color) {

  // take the chip select low to select the device:
  digitalWrite(chipSelectPin, LOW);
  //delay(5);

  SPI.transfer(color); //Send register location

  //delay(5);
  // take the chip select high to de-select:
  digitalWrite(chipSelectPin, HIGH);
}

