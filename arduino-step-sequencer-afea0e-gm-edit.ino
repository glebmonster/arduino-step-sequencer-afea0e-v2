/*
 * Code originally from https://create.arduino.cc/projecthub/eEdizon/arduino-step-sequencer-afea0e
 * Licensed under © GPL3+
 * 
 * Description from https://makeyouruno.arduino.cc/makeyouruno/module/projects/lesson/04-make-your-synth-shield
 * The Synth Shield has 6x control knobs (potentiometers) and a speaker for sound output. 
 * These can be combined to produce various types of sounds.
 * Analog pins A0-A4 are connected to the 4 potentiometers on the left and the bottom right one. 
 * The top right potentiometer adjusts the volume of the speaker (connected to D9).
 * 
 * Additional comment:
 * This is an updated version of the project listed above. 
 * A0-A3 - define one note each, forming an arpeggio, in a loop.
 * A4 defines the arpeggio speed.
 * The LED-related parts have been removed, as they are not utilised in the Make Your Uno kit.
 */

const byte speaker = 9; // Speaker pin
bool debug = false; // Used to print values to Serial Monitor
//bool isOn = false;   // Checks if the device should work or not // Not in use
long counter = 0;   // Used for speed
long tempo;         // Used for reading the speed
int lowFreq = 10;   // The lower frequency boundary
int highFreq = 2000; // The higher frequency boundary
int pattern = 0;    // Current potentiometer
unsigned int note;  // Note that will be played

int getNote(int pattern) {  // Get notes for specific patterns
  note = map(analogRead(pattern+14), 0, 1023, lowFreq, highFreq);
  return note;
}

void setup() {
}

void loop() {
  tempo = map(analogRead(A4), 0, 1023, 4000, 100); // Reverse mapping
  if (tempo < 3900) {// Enter if speed still acceptable
  if(counter > tempo) {
    if(debug) {
      Serial.println(pattern);
    }
    noTone(speaker);
    counter=0;   
    note = getNote(pattern);    
    pattern = (pattern+1)%4;
    if(note>lowFreq+10) {
      tone(speaker, note);
    }
  }
  counter++;
  } else { //Stopped on a specific potentiometer
    note = map(analogRead(pattern), 0, 1023, lowFreq, highFreq);
    if (note > lowFreq + 10) {
      tone(speaker, note);
    } else {
      noTone(speaker);
    }
  }
}
