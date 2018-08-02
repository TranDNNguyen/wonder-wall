/****************************************************************
ProximityTest.ino
APDS-9960 RGB and Gesture Sensor
Shawn Hymel @ SparkFun Electronics
October 28, 2014
https://github.com/sparkfun/APDS-9960_RGB_and_Gesture_Sensor

Tests the proximity sensing abilities of the APDS-9960.
Configures the APDS-9960 over I2C and polls for the distance to
the object nearest the sensor.

Hardware Connections:

IMPORTANT: The APDS-9960 can only accept 3.3V!
 
 Arduino Pin  APDS-9960 Board  Function
 
 3.3V         VCC              Power
 GND          GND              Ground
 A4           SDA              I2C Data
 A5           SCL              I2C Clock

Resources:
Include Wire.h and SparkFun_APDS-9960.h

Development environment specifics:
Written in Arduino 1.0.5
Tested with SparkFun Arduino Pro Mini 3.3V

This code is beerware; if you see me (or any other SparkFun 
employee) at the local, and you've found our code helpful, please
buy us a round!

Distributed as-is; no warranty is given.
****************************************************************/

#include <Wire.h>
#include <SparkFun_APDS9960.h>

// Global Variables
SparkFun_APDS9960 apds = SparkFun_APDS9960();
uint8_t proximity_data = 0;

void setup() {
  
  // Initialize Serial port
  Serial.begin(9600);
  Serial1.begin(31250);
  Serial.println();
  Serial.println(F("------------------------------------"));
  Serial.println(F("SparkFun APDS-9960 - ProximitySensor"));
  Serial.println(F("------------------------------------"));
  
  // Initialize APDS-9960 (configure I2C and initial values)
  if ( apds.init() ) {
    Serial.println(F("APDS-9960 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }
  
  // Adjust the Proximity sensor gain
  if ( !apds.setProximityGain(PGAIN_2X) ) {
    Serial.println(F("Something went wrong trying to set PGAIN"));
  }
  
  // Start running the APDS-9960 proximity sensor (no interrupts)
  if ( apds.enableProximitySensor(false) ) {
    Serial.println(F("Proximity sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during sensor init!"));
  }
}

void noteOn(int cmd, int pitch, int velocity) {
  Serial1.write(cmd);
  Serial1.write(pitch);
  Serial1.write(velocity);
}
byte note = 0; //The MIDI note value to be played
byte resetMIDI = 4; //Tied to VS1053 Reset line
byte ledPin = 13; //MIDI traffic inidicator
int  instrument = 14;
int tune[13] = {69, 68, 67, 68, 69, 69, 69, 68, 68, 68, 69, 71, 71}; //Mary had a little lamb pt 1
int tune2[13] = {69, 68, 67, 68, 69, 69, 69, 69, 68, 68, 69, 68, 66}; //Mary had a little lamb pt 2

/*   The notes used for any instruments in the "melodic" bank range from 30-90 
 *   and contain five 12-note octaves (ie notes from 30-42 for the lowest octave, 
 *   78-90 for the highest octave).
 *   Instruments in the percussion bank don't need notes - once the bank is selected, just
 *   select the instrument we need and play note 30 */

//Send a MIDI note-on message.  Like pressing a piano key
//channel ranges from 0-15
void noteOn(byte channel, byte note, byte attack_velocity) {
  talkMIDI( (0x90 | channel), note, attack_velocity);
}

//Send a MIDI note-off message.  Like releasing a piano key
void noteOff(byte channel, byte note, byte release_velocity) {
  talkMIDI( (0x80 | channel), note, release_velocity);
}


//Plays a MIDI note. Doesn't check to see that cmd is greater than 127, or that data values are less than 127
void talkMIDI(byte cmd, byte data1, byte data2) {
  //digitalWrite(ledPin, HIGH);
  Serial1.write(cmd);
  Serial1.write(data1);

  //Some commands only have one data byte. All cmds less than 0xBn have 2 data bytes 
  //(sort of: http://253.ccarh.org/handout/midiprotocol/)
  if( (cmd & 0xF0) <= 0xB0)
    Serial1.write(data2);

  //digitalWrite(ledPin, LOW);
}

void loop() {

  // Read the proximity value
  if ( !apds.readProximity(proximity_data) ) {
    Serial.println("Error reading proximity value");
  } else {
    Serial.print("Proximity: ");
    Serial.println(proximity_data);
  }
  if(proximity_data > 120){
    proximity_data = 120;
  }


  int instrument = 0;
   talkMIDI(0xB0, 0, 0x00); //Default bank GM1

    talkMIDI(0xC0, instrument, 24); //Sets the instrument to be used. 0xC0 is a 1 data byte command


   int note = 120;
   
    noteOn(0x90, note, proximity_data);
    delay(350);
    noteOff(0x90, note, 0x45);

}


   /*
   for (int note = 0x1E; note < 0x5A; note ++) {
    //Note on channel 1 (0x90), some note value (note), middle velocity (0x45):
    noteOn(0x90, note, proximity_data);
    delay(100);
    noteOff(0x90, note, 0x45);
    delay(250);
    //Note on channel 1 (0x90), some note value (note), silent velocity (0x00):
    noteOn(0x90, note, 0x00);   
  }
  */

/*
 * SysEx device control: 0x01 : master volume (only in file mode!)
channel message: 0x80 note off, 0x90 note on, 0xc0 program, 0xe0 pitch wheel
channel message 0xb0: parameter
0x00: bank select (0 is default, 0x78 and 0x7f is drums, 0x79 melodic)
0x06: RPN MSB: 0 = bend range, 2 = coarse tune
0x07: channel volume
0x0a: pan control
0x0b: expression (changes volume)
0x0c: effect control 1 (sets global reverb decay)
0x26: RPN LSB: 0 = bend range
0x40: hold1
0x42: sustenuto
0x5b effects level (channel reverb level)
0x62,0x63,0x64,0x65: NRPN and RPN selects
0x78: all sound off
0x79: reset all controllers
0x7b, 0x7c, 0x7d: all notes off
 * 
 * */
