#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX



void setup() {

  // set MIDI baud rate
  mySerial.begin(31250);
  Serial.begin(9600);
}

// variables to be sent from the master device
            

  int input[8] = {1, 6, 2, 5, 3, 6, 4, 5};    // 1x8 array of integer with different integers representing different chord
  int position;       // the column that is being played at a certain time (ranges from 0 to 7)
 

// variables for this code
  int instrument[6] = {1, 14, 31, 39, 51, 82};    // list of instruments to be declared (Acoustic Grand Piano, Xylophone, Distortion Guitar, Synth Bass 1, Synth Strings 1, Saw Lead)

void loop() {
  position = 0;
  talkMIDI(0xB0, 0, 0x79); // melodic bank
  while (position < 8)
  {
    playNote(position);
    position++;
  }
  position = 0;

}


// this function goes down the n-th column, checks the type of the instrument(the color of the cube), and plays a note. it will play notes concurrently if there are more than one block in the column
void playNote(int n)  {
  
  switch(input[n])
  {
    case 1:
      playArppegio_M(48);
      break;
    case 2:
      playArppegio_m(50);
      break;
    case 3:
      playArppegio_m(52);
      break;
    case 4:
      playArppegio_M(41);
      break;
    case 5:
      playArppegio_M(43);
      break;
    case 6:
      playArppegio_m(45);
      break;
  } 
  
//  for (int i = 0; i < 7; i++) {
//    if (input[i][n] != 0) {
//      talkMIDI(0xC0, instrument[input[i][n]-1], 0);
//      noteOn(0x90, note[i], 30);
//    }
//    else  {
//      continue;
//    }
//  }
}

void playArppegio_M(int n)
{
  talkMIDI(0xC0, 13, 0);
  
  noteOn(0x90, n, 30);
  delay(250);
  noteOn(0x90, n+4, 30);
  delay(250);
  noteOn(0x90, n+7, 30);
  delay(250);
  noteOn(0x90, n+12, 30);
  delay(250);
  noteOn(0x90, n+7, 30);
  delay(250);
  noteOn(0x90, n+4, 30);
  delay(250);
  noteOn(0x90, n, 30);
  delay(250);
  noteOn(0x90, n+4, 30);
  delay(250);
}

void playArppegio_m(int n)
{
  talkMIDI(0xC0, 13, 0);
  
  noteOn(0x90, n, 30);
  delay(250);
  noteOn(0x90, n+3, 30);
  delay(250);
  noteOn(0x90, n+7, 30);
  delay(250);
  noteOn(0x90, n+12, 30);
  delay(250);
  noteOn(0x90, n+7, 30);
  delay(250);
  noteOn(0x90, n+3, 30);
  delay(250);
  noteOn(0x90, n, 30);
  delay(250);
  noteOn(0x90, n+3, 30);
  delay(250);
}
      
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
  mySerial.write(cmd);
  mySerial.write(data1);

  //Some commands only have one data byte. All cmds less than 0xBn have 2 data bytes 
  //(sort of: http://253.ccarh.org/handout/midiprotocol/)
  if( (cmd & 0xF0) <= 0xB0)
    mySerial.write(data2);

  //digitalWrite(ledPin, LOW);
}
  

  

