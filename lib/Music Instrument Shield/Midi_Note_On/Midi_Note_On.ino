/*
 MIDI note player
 
 This sketch shows how to use the serial transmit pin (pin 1) to send MIDI note data.
 If this circuit is connected to a MIDI synth, it will play 
 the notes F#-0 (0x1E) to F#-5 (0x5A) in sequence.

 
 The circuit:
 * digital in 1 connected to MIDI jack pin 5
 * MIDI jack pin 2 connected to ground
 * MIDI jack pin 4 connected to +3.3V through 220-ohm resistor
 Attach a MIDI cable to the jack, then to a MIDI synth, and play music.

 created 13 Jun 2006
 modified 30 Aug 2011
 by Tom Igoe 

 This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/MIDI
 
 */

void setup() {
  //  Set MIDI baud rate:
  Serial1.begin(31250);
}

void loop() {


  //Select instrument bank
  talkMIDI(0xB0, 0, 0x79); //Set instrument bank. 0x7f for percussion, 0x79 for medlodic
  talkMIDI(0xC0, 35, 0);

  //Change to different instrument
   for(int instrument = 0; instrument < 127; instrument++)
  {
      talkMIDI(0xC0, instrument, 0);
      noteOn(0x90, 60, 0x25);
      noteOff(0x90, 60, 0x25);
      delay(250);
      //talkMIDI(0xC0, instrument+1, 0);
      //noteOn(0x90, 60, 0x25);
      
  }
}

//  plays a MIDI note.  Doesn't check to see that
//  cmd is greater than 127, or that data values are  less than 127:
/*void noteOn(int cmd, int pitch, int velocity) {
  Serial1.write(cmd);
  Serial1.write(pitch);
  Serial1.write(velocity);
}*/

/*
 *   for(int instrument = 0; instrument < 127; instrument++)
  {
      talkMIDI(0xC0, instrument, 0);
      noteOn(0x90, 60, 0x25);
      //noteOff(0x90, 60, 0x25);
      delay(50);
      delay(2000);
      //talkMIDI(0xC0, instrument+1, 0);
      //noteOn(0x90, 60, 0x25);
      
  }
 */
 
/*
 * //Change to different instrument
  for(instrument = 0 ; instrument < 127 ; instrument++) {

    Serial1.print(" Instrument: ");
    Serial1.println(instrument, DEC);

    talkMIDI(0xC0, instrument, 0); //Set instrument number. 0xC0 is a 1 data byte command

    //Play notes from F#-0 (30) to F#-5 (90):
    for (note = 30 ; note < 40 ; note++) {
      Serial1.print("N:");
      Serial1.println(note, DEC);
      
      //Note on channel 1 (0x90), some note value (note), middle velocity (0x45):
      noteOn(0, note, 60);
      delay(50);

      //Turn off the note with a given off/release velocity
      noteOff(0, note, 60);
      delay(50);
    }

    delay(100); //Delay between instruments
  }
  */

  /*
  // play notes from F#-0 (0x1E/30) to F#-5 (0x5A/90):
  for (int note = 0x1E; note < 0x5A; note ++) {
    //Note on channel 1 (0x90), some note value (note), middle velocity (0x45):
    noteOn(0x90, note, 0x25);
    delay(100);
    //Note on channel 1 (0x90), some note value (note), silent velocity (0x00):
    noteOn(0x90, note, 0x00);   
    delay(100);
  }
  */
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
