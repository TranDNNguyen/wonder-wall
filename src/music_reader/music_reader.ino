void setup() {

  // set MIDI baud rate
  Serial1.begin(31250);

  // variables to be sent from the master device
  int input[7][8] = {
            {0, 0, 0, 0, 0, 0, 0, 0}
            {0, 0, 0, 0, 0, 0, 0, 0}
            {0, 0, 0, 3, 3, 0, 0, 0}
            {0, 0, 2, 0, 0, 2, 0, 0}
            {1, 1, 0, 0, 0, 0, 1, 0}
            {0, 0, 0, 0, 0, 0, 0, 0}
            {0, 0, 0, 0, 0, 0, 0, 0}}
            {;    // 7x8 array of integer with different integers representing different instruments
  }
  int position;       // the column that is being played at a certain time (ranges from 0 to 7)

  // variables for this code
  int note[7] = {65, 67, 69, 70, 72, 74, 76}; // notes to be played (F Major Scale)
  int instrument[6] = {1, 14, 31, 39, 51, 82};    // list of instruments to be declared (Acoustic Grand Piano, Xylophone, Distortion Guitar, Synth Bass 1, Synth Strings 1, Saw Lead)
  




}

void loop() {

  talkMIDI(0xB0, 0, 0x79); // melodic bank

  // looks at the position, and calls for a function playNote
  switch(position)
  {
    case 0:
      playNote(0);
    case 1:
      playNote(1);
    case 2:
      playNote(2); 
    case 3:
      playNote(3);
    case 4:
      playNote(4);
    case 5:
      playNote(5);
    case 6:
      playNote(6);
    case 7:
      playNote(7);
  }

}


// this function goes down the n-th column, checks the type of the instrument(the color of the cube), and plays a note. it will play notes concurrently if there are more than one block in the column
void playNote(int n)  {
  
  for (int i = 0; i < 7; i++) {
    if (input[i][n] != 0) {
      talkMIDI(0xC0, instrument[input[i][n]], 0);
      noteOn(0x90, note[i], 60);
    }
    else  {
      continue:
    }
  }
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
  Serial1.write(cmd);
  Serial1.write(data1);

  //Some commands only have one data byte. All cmds less than 0xBn have 2 data bytes 
  //(sort of: http://253.ccarh.org/handout/midiprotocol/)
  if( (cmd & 0xF0) <= 0xB0)
    Serial1.write(data2);

  //digitalWrite(ledPin, LOW);
}
  

  

