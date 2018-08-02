#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX

void setup() {
  
  mySerial.begin(31250);
}

int input[8] = {6,1,2,0,0,0,1,4};
int instrument[11] = {44, 46, 38, 40, 36, 49, 51, 39, 56, 60, 61};

 
int HH[7][16] = {{1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0},
                 {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
                 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                 {1,1,1,1,0,1,0,1,1,0,1,1,1,0,1,0},
                 {1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2},                 
                 {0,0,2,0,0,0,2,0,0,0,2,0,0,0,2,0},
                 {9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9}};

int Sn[7][16] = {{0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0},
                 {1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0},
                 {0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0},
                 {0,1,0,0,1,0,0,1,0,1,1,0,1,1,0,1},
                 {0,0,0,0,1,0,0,0,0,0,0,0,1,1,1,1},
                 {0,0,0,0,2,0,0,2,0,2,0,0,2,0,0,0},
                 {9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9}};

                 
 
int Ba[7][16] = {{1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
                 {1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0},
                 {1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0},
                 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                 {1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1},
                 {1,0,0,1,0,0,0,0,0,0,0,0,0,1,0,1},
                 {9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9}};

                 
 
int Cy[7][16] = {{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                 {1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0},
                 {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
                 {0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0},
                 {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
                 {1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1},
                 {9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9}};


                 
int Ri[7][16] = {{1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0},
                 {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
                 {1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1},
                 {1,0,1,1,0,0,1,1,0,1,1,0,1,1,0,1},
                 {0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0},
                 {1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1},
                 {9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9}};


int Cl[7][16] = {{0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0},
                 {1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0},
                 {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
                 {0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0},
                 {0,0,1,0,0,0,1,0,0,1,0,0,1,0,1,1},
                 {0,0,0,0,1,0,0,0,0,0,0,0,1,1,1,1},
                 {9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9}};


int Cb[7][16] = {{1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0},
                 {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
                 {0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0},
                 {0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
                 {0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0},
                 {0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
                 {9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9}};



int Bo[7][16] = {{1,0,1,0,1,0,0,0,0,1,0,0,1,0,2,0},
                 {1,0,1,0,1,0,2,2,1,0,1,0,1,0,2,2},
                 {1,1,2,2,1,1,2,2,0,0,1,1,2,2,0,0},
                 {1,0,0,1,1,0,2,2,1,0,0,1,1,0,2,2},
                 {2,1,2,2,1,2,2,1,2,2,1,2,2,1,1,2},
                 {1,0,0,0,1,0,0,0,1,0,0,0,2,0,2,0},
                 {9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9}};


void loop() {
  talkMIDI(0xB0, 0, 0x89);
  talkMIDI(0xC0, 30, 0);


  notePlay(0);
  delay(125);
  notePlay(1);
  delay(125);
  notePlay(2);
  delay(125);
  notePlay(3);
  delay(125);
  notePlay(4);
  delay(125);
  notePlay(5);
  delay(125);
  notePlay(6);
  delay(125);
  notePlay(7);
  delay(125);
  notePlay(8);
  delay(125);
  notePlay(9);
  delay(125);
  notePlay(10);
  delay(125);
  notePlay(11);
  delay(125);
  notePlay(12);
  delay(125);
  notePlay(13);
  delay(125);
  notePlay(14);
  delay(125);
  notePlay(15);
  delay(125);
  
}
  void notePlay(int n){
  
    if (HH[input[0]-1][n]==0 || Sn[input[0]-1][n]==0 || Ba[input[0]-1][n]==0 || Cy[input[0]-1][n]==0 || Ri[input[0]-1][n]==0 || Cl[input[0]-1][n]==0 || Cb[input[0]-1][n]==0 || Bo[input[0]-1][n]==0){
      Mute();
    }
    if (HH[input[0]-1][n]==1){
      HHclose();
    }
    if (HH[input[0]-1][n]==2){
      HHopen();
    }
    if (Sn[input[1]-1][n]==1){
      ASnare();
    }
    if (Sn[input[1]-1][n]==2){
      ESnare();
    }
    if (Ba[input[2]-1][n]==1){
      Bass();
    }
    if (Cy[input[3]-1][n]==1){
      Crash();
    }
    if (Ri[input[4]-1][n]==1){
      Ride();
    }
    if (Cl[input[5]-1][n]==1){
      Clap();
    }
    if (Cb[input[6]-1][n]==1){
      Cowbell();
    }
    if (Bo[input[7]-1][n]==1){
      BongoL();
    }
    if (Bo[input[7]-1][n]==2){
      BongoH();
    }


    
    
  }

  

  void HHopen(){noteOn(0, instrument[0], 15);}
  void HHclose(){noteOn(0, instrument[1], 15);}
  void ASnare(){noteOn(0, instrument[2], 20);}
  void ESnare(){noteOn(0, instrument[3], 20);}
  void Bass(){noteOn(0, instrument[4], 20);}
  void Crash(){noteOn(0, instrument[5], 20);}
  void Ride(){noteOn(0, instrument[6], 20);}
  void Clap(){noteOn(0, instrument[7], 20);}
  void Cowbell(){noteOn(0, instrument[8], 20);}
  void BongoH(){noteOn(0, instrument[9], 20);}
  void BongoL(){noteOn(0, instrument[10], 20);}
  void Mute(){noteOn(0, instrument[0], 0);}



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
  
