#include <Wire.h>
#include <SPI.h>
extern "C" { 
#include "utility/twi.h"  // from Wire library, so we can do bus scanning
}

#include <SparkFun_APDS9960.h>


//Device Addresses
#define TCAADDR 0x70
#define APDSADDR 0x39

// pins used for the connection with the sensor
// the other you need are controlled by the SPI library):
const int chipSelectPin = 10; // pin 10 / LA CH1
//MOSI: pin 11 / LA CH3
//SCK: pin 13 / LA CH2

//Global variables
SparkFun_APDS9960 sensor = SparkFun_APDS9960();

uint16_t red_light = 0;
uint16_t green_light = 0;
uint16_t blue_light = 0;
uint8_t proximity_data = 0;
uint8_t sen_Sel;
uint8_t mux_Sel;
uint8_t k;  //temp, change this later
char buff[128];     // buffer to store formatted outputs to serial

void tcaselect(uint8_t sen, uint8_t tca_Adr) {
  
  //tca_Adr = 0x70 + tca_Adr; // get mux address
  
  if (sen > 6) return;
  else if(sen >= 0){  // Valid sensor selection
    Wire.beginTransmission(0x70 + tca_Adr);
    Wire.write(1 << sen); 
    Wire.endTransmission(); 
  }
  else{  // negative values turn off the mux
    Wire.beginTransmission(0x70 + tca_Adr);
    Wire.write(0);
    Wire.endTransmission();
  }
  
}

void setup() {
  // put your setup code here, to run once:
  while(!Serial);
  delay(1000);

  Wire.begin();

  Serial.begin(9600);
  Serial.println("\nTCA ready!");

  //Initialize sensors
  for(k = 0; k <= 1; k++){

    // switch between the two muxes being used
    if(k == 0){
      mux_Sel = 2;
      tcaselect(5, -1); // turn off mux 5
    }
    else if(k == 1){
      mux_Sel = 5;
      tcaselect(2, -1); // turn off mux 2
    }
      
    for(sen_Sel = 0; sen_Sel <= 6; sen_Sel++){
      tcaselect(mux_Sel,sen_Sel);
      
      if(!sensor.init()){
        sprintf(buff,"Failed to initialize sensor %d\n", sen_Sel);
        Serial.println(buff);
        while(1);
      }
      else{
        sprintf(buff,"Sensor%1d initialized", sen_Sel);
        Serial.println(buff);
      }
    
      // Adjust the Proximity sensor gain
      if ( !sensor.setProximityGain(PGAIN_2X) ) {
        Serial.println(F("Something went wrong trying to set PGAIN"));
      }
      
      // Start running the APDS-9960 light sensor (no interrupts)
      if ( sensor.enableLightSensor(false) ) {
        Serial.println(F("Light sensor is now running"));
      } else {
        Serial.println(F("Something went wrong during light sensor init!"));
      }
    
      // Start running the APDS-9960 proximity sensor (no interrupts)
      if ( sensor.enableProximitySensor(false) ) {
        Serial.println(F("Proximity sensor is now running"));
      } else {
        Serial.println(F("Something went wrong during sensor init!"));
      }
      // Wait for initialization and calibration to finish
      delay(250);
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  for(k = 0; k <= 1; k++){

    if(k == 0){
      mux_Sel = 2;
      tcaselect(5, -1); // turn off mux 5
    }
    else if(k == 1){
      mux_Sel = 5;
      tcaselect(2, -1); // turn off mux 2
    }
      
    // read data from selected mux
    for(sen_Sel = 0; sen_Sel <= 6; sen_Sel++){
      tcaselect(sen_Sel, mux_Sel);
      // Read the light levels (ambient, red, green, blue)
      if (  //!apds.readAmbientLight(ambient_light) ||
            !sensor.readRedLight(red_light) ||
            !sensor.readGreenLight(green_light) ||
            !sensor.readBlueLight(blue_light) ) {
        Serial.println("Error reading light values");
      } else {
        sprintf(buff,"/////SENSOR %d ON MUX %d/////", sen_Sel, mux_Sel);
        Serial.println(buff);
        Serial.print(" Red: ");
        Serial.print(red_light);
        Serial.print(" Green: ");
        Serial.print(green_light);
        Serial.print(" Blue: ");
        Serial.print(blue_light);
      }
        if ( !sensor.readProximity(proximity_data) ) {
        Serial.println("Error reading proximity value");
      } else {
        Serial.print(" Proximity: ");
        Serial.println(proximity_data);
        Serial.println("////////");
      }
      delay(250);
    }
  }
}
