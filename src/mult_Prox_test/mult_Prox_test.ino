#include <Wire.h>
extern "C" { 
#include "utility/twi.h"  // from Wire library, so we can do bus scanning
}

#include <SparkFun_APDS9960.h>


//Device Addresses
#define TCAADDR 0X70
#define APDSADDR 0x39

//Global variables
SparkFun_APDS9960 sensor = SparkFun_APDS9960();

uint16_t red_light = 0;
uint16_t green_light = 0;
uint16_t blue_light = 0;
uint8_t proximity_data = 0;

void tcaselect(uint8_t i) {
  if (i > 7) return;
 
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i); 
  Wire.endTransmission();
}

void setup() {
  // put your setup code here, to run once:
  while(!Serial);
  delay(1000);

  Wire.begin();

  Serial.begin(9600);
  Serial.println("\nTCA ready!");

  //Initialize sensors
  tcaselect(0);
  if(!sensor.init()){
    Serial.println("Failed to initialize sensor 1\n");
    while(1);
  }
  else
    Serial.println("Sensor1 initialized");

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
  delay(500);

  tcaselect(1);
  if(!sensor.init()){
    Serial.println("Failed to initialize sensor 1\n");
    while(1);
  }
  else
    Serial.println("Sensor1 initialized");

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
  delay(500);

  tcaselect(2);
  if(!sensor.init()){
    Serial.println("Failed to initialize sensor 1\n");
    while(1);
  }
  else
    Serial.println("Sensor1 initialized");

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
  delay(500);



  tcaselect(3);
  if(!sensor.init()){
    Serial.println("Failed to initialize sensor 2\n");
    while(1);
  }
  else
    Serial.println("Sensor2 initialized");

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
  delay(500);

  tcaselect(4);
  if(!sensor.init()){
    Serial.println("Failed to initialize sensor 1\n");
    while(1);
  }
  else
    Serial.println("Sensor1 initialized");

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
  delay(500);

  tcaselect(5);
  if(!sensor.init()){
    Serial.println("Failed to initialize sensor 1\n");
    while(1);
  }
  else
    Serial.println("Sensor1 initialized");

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
  delay(500);

  tcaselect(6);
  if(!sensor.init()){
    Serial.println("Failed to initialize sensor 1\n");
    while(1);
  }
  else
    Serial.println("Sensor1 initialized");

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
  delay(500);

  tcaselect(7);
  if(!sensor.init()){
    Serial.println("Failed to initialize sensor 1\n");
    while(1);
  }
  else
    Serial.println("Sensor1 initialized");

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
  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:

  //read data from sensor 1
  tcaselect(0);
  // Read the light levels (ambient, red, green, blue)
  if (  //!apds.readAmbientLight(ambient_light) ||
        !sensor.readRedLight(red_light) ||
        !sensor.readGreenLight(green_light) ||
        !sensor.readBlueLight(blue_light) ) {
    Serial.println("Error reading light values");
  } else {
    //Serial.print("Ambient: ");
    //Serial.print(ambient_light);
    Serial.println("/////SENSOR 1/////");
    Serial.print(" Red1: ");
    Serial.print(red_light);
    Serial.print(" Green1: ");
    Serial.print(green_light);
    Serial.print(" Blue1: ");
    Serial.print(blue_light);
  }
    if ( !sensor.readProximity(proximity_data) ) {
    Serial.println("Error reading proximity value");
  } else {
    Serial.print(" Proximity1: ");
    Serial.println(proximity_data);
    Serial.println("////////");
  }
  delay(500);

  tcaselect(1);
  // Read the light levels (ambient, red, green, blue)
  if (  //!apds.readAmbientLight(ambient_light) ||
        !sensor.readRedLight(red_light) ||
        !sensor.readGreenLight(green_light) ||
        !sensor.readBlueLight(blue_light) ) {
    Serial.println("Error reading light values");
  } else {
    //Serial.print("Ambient: ");
    //Serial.print(ambient_light);
    Serial.println("/////SENSOR 2/////");
    Serial.print(" Red2: ");
    Serial.print(red_light);
    Serial.print(" Green2: ");
    Serial.print(green_light);
    Serial.print(" Blue2: ");
    Serial.print(blue_light);
  }
    if ( !sensor.readProximity(proximity_data) ) {
    Serial.println("Error reading proximity value");
  } else {
    Serial.print(" Proximity2: ");
    Serial.println(proximity_data);
    Serial.println("////////");
  }
  delay(500);

  tcaselect(2);
  // Read the light levels (ambient, red, green, blue)
  if (  //!apds.readAmbientLight(ambient_light) ||
        !sensor.readRedLight(red_light) ||
        !sensor.readGreenLight(green_light) ||
        !sensor.readBlueLight(blue_light) ) {
    Serial.println("Error reading light values");
  } else {
    //Serial.print("Ambient: ");
    //Serial.print(ambient_light);
    Serial.println("/////SENSOR 3/////");
    Serial.print(" Red3: ");
    Serial.print(red_light);
    Serial.print(" Green3: ");
    Serial.print(green_light);
    Serial.print(" Blue3: ");
    Serial.print(blue_light);
  }
    if ( !sensor.readProximity(proximity_data) ) {
    Serial.println("Error reading proximity value");
  } else {
    Serial.print(" Proximity3: ");
    Serial.println(proximity_data);
    Serial.println("////////");
  }
  delay(500);
  
  //Read data from sensor 2
  tcaselect(3);
  // Read the light levels (ambient, red, green, blue)
  if (  //!apds.readAmbientLight(ambient_light) ||
        !sensor.readRedLight(red_light) ||
        !sensor.readGreenLight(green_light) ||
        !sensor.readBlueLight(blue_light) ) {
    Serial.println("Error reading light values");
  } else {
    //Serial.print("Ambient: ");
    //Serial.print(ambient_light);
    Serial.println("/////SENSOR 4/////");
    Serial.print(" Red4: ");
    Serial.print(red_light);
    Serial.print(" Green4: ");
    Serial.print(green_light);
    Serial.print(" Blue4: ");
    Serial.print(blue_light);
  }
    if ( !sensor.readProximity(proximity_data) ) {
    Serial.println("Error reading proximity value");
  } else {
    Serial.print(" Proximity4: ");
    Serial.println(proximity_data);
    Serial.println("////////");
  }

  delay(500);

  tcaselect(4);
  // Read the light levels (ambient, red, green, blue)
  if (  //!apds.readAmbientLight(ambient_light) ||
        !sensor.readRedLight(red_light) ||
        !sensor.readGreenLight(green_light) ||
        !sensor.readBlueLight(blue_light) ) {
    Serial.println("Error reading light values");
  } else {
    //Serial.print("Ambient: ");
    //Serial.print(ambient_light);
    Serial.println("/////SENSOR 5/////");
    Serial.print(" Red5: ");
    Serial.print(red_light);
    Serial.print(" Green5: ");
    Serial.print(green_light);
    Serial.print(" Blue5: ");
    Serial.print(blue_light);
  }
    if ( !sensor.readProximity(proximity_data) ) {
    Serial.println("Error reading proximity value");
  } else {
    Serial.print(" Proximity5: ");
    Serial.println(proximity_data);
    Serial.println("////////");
  }
  delay(500);

  tcaselect(5);
  // Read the light levels (ambient, red, green, blue)
  if (  //!apds.readAmbientLight(ambient_light) ||
        !sensor.readRedLight(red_light) ||
        !sensor.readGreenLight(green_light) ||
        !sensor.readBlueLight(blue_light) ) {
    Serial.println("Error reading light values");
  } else {
    //Serial.print("Ambient: ");
    //Serial.print(ambient_light);
    Serial.println("/////SENSOR 6/////");
    Serial.print(" Red6: ");
    Serial.print(red_light);
    Serial.print(" Green6: ");
    Serial.print(green_light);
    Serial.print(" Blue6: ");
    Serial.print(blue_light);
  }
    if ( !sensor.readProximity(proximity_data) ) {
    Serial.println("Error reading proximity value");
  } else {
    Serial.print(" Proximity6: ");
    Serial.println(proximity_data);
    Serial.println("////////");
  }
  delay(500);

  tcaselect(6);
  // Read the light levels (ambient, red, green, blue)
  if (  //!apds.readAmbientLight(ambient_light) ||
        !sensor.readRedLight(red_light) ||
        !sensor.readGreenLight(green_light) ||
        !sensor.readBlueLight(blue_light) ) {
    Serial.println("Error reading light values");
  } else {
    //Serial.print("Ambient: ");
    //Serial.print(ambient_light);
    Serial.println("/////SENSOR 7/////");
    Serial.print(" Red7: ");
    Serial.print(red_light);
    Serial.print(" Green7: ");
    Serial.print(green_light);
    Serial.print(" Blue7: ");
    Serial.print(blue_light);
  }
    if ( !sensor.readProximity(proximity_data) ) {
    Serial.println("Error reading proximity value");
  } else {
    Serial.print(" Proximity7: ");
    Serial.println(proximity_data);
    Serial.println("////////");
  }
  delay(500);

  tcaselect(7);
  // Read the light levels (ambient, red, green, blue)
  if (  //!apds.readAmbientLight(ambient_light) ||
        !sensor.readRedLight(red_light) ||
        !sensor.readGreenLight(green_light) ||
        !sensor.readBlueLight(blue_light) ) {
    Serial.println("Error reading light values");
  } else {
    //Serial.print("Ambient: ");
    //Serial.print(ambient_light);
    Serial.println("/////SENSOR 8/////");
    Serial.print(" Red8: ");
    Serial.print(red_light);
    Serial.print(" Green8: ");
    Serial.print(green_light);
    Serial.print(" Blue8: ");
    Serial.print(blue_light);
  }
    if ( !sensor.readProximity(proximity_data) ) {
    Serial.println("Error reading proximity value");
  } else {
    Serial.print(" Proximity8: ");
    Serial.println(proximity_data);
    Serial.println("////////");
  }
  delay(500);
}
