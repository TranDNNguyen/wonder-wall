#include <Wire.h>

#include <SparkFun_APDS9960.h>


//Device Addresses
#define TCAADDR1 0x70
#define TCAADDR2 0x71
#define APDSADDR 0x39

//Global variables
SparkFun_APDS9960 sensor = SparkFun_APDS9960();
uint16_t red_light = 0;
uint16_t green_light = 0;
uint16_t blue_light = 0;
uint8_t proximity_data = 0;

void tcaselect1(uint8_t i) {
  if (i > 7) return;
 
  Wire.beginTransmission(TCAADDR1);
  Wire.write(1 << i);
  Wire.endTransmission();
}

void tcaselect2(uint8_t i) {
  if (i > 7) return;
 
  Wire.beginTransmission(TCAADDR2);
  Wire.write(1 << i);
  Wire.endTransmission();
}

void tcaselect_end1() 
{
  Wire.beginTransmission(TCAADDR1);
  Wire.write(0);
  Wire.endTransmission();
}

void tcaselect_end2() 
{
  Wire.beginTransmission(TCAADDR2);
  Wire.write(0);
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
  tcaselect1(0);
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
  tcaselect_end1();
  delay(500);
  

  tcaselect2(0);
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
  tcaselect_end2();
  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:

  //read data from sensor 1
  tcaselect_end2();
  tcaselect1(0);
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
  //delay(500);
  
  //Read data from sensor 2
  tcaselect_end1();
  tcaselect2(0);
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
  //delay(500);
}
