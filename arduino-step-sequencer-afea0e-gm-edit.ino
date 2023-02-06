/*
 * Code originally from 
 * https://create.arduino.cc/projecthub/eEdizon/arduino-step-sequencer-afea0e
 * https://www.hackster.io/eEdizon/arduino-step-sequencer-afea0e
 * Licensed under © GPL3+
 * 
 * Project originally from 
 * https://makeyouruno.arduino.cc/makeyouruno/module/projects/lesson/04-make-your-synth-shield
 * 
 * Additional comment:
 * This is an updated version of the projects listed above. 
 * An assembled synth must be horizontally oriented, like this: [:::O]
 * The four knobs on the left adjust audio frequencies, one note each (connected to A0-A3).
 * Together they make an arpeggio, playing in a loop.
 * The top right potentiometer adjusts the volume of the speaker (connected to D9).
 * The bottom right potentiometer adjusts the arpeggiator tempo (connected to A4).
 * The LED-related parts have been removed, as they are not utilised in the Make Your Uno kit.
 */

const byte speaker = 9; // Speaker pin
bool debug = false;     // Used to print values to Serial Monitor
//bool isOn = false;    // Checks if the device should work or not // Currently not in use
long counter = 0;       // Used for speed
long tempo;             // Used for reading the speed
int lowFreq = 10;       // The lower frequency boundary
int highFreq = 2000;    // The higher frequency boundary
int pattern = 0;        // Current potentiometer
unsigned int note;      // Note that will be played

int getNote(int pattern) {  
  // Get notes for specific patterns
  note = map(analogRead(pattern+14), 0, 1023, lowFreq, highFreq);
  return note;
}

void setup() {
}

void loop() {
  tempo = map(analogRead(A4), 0, 1023, 4000, 100); // Reverse mapping
  if (tempo < 3900) { // Enter if speed still acceptable
    if(counter > tempo) {
      if(debug) {
        Serial.println(pattern);
      }
      noTone(speaker);
      counter = 0;   
      note = getNote(pattern);    
      pattern = (pattern + 1) % 4;
      if(note > lowFreq + 10) {
        tone(speaker, note);
      }
    }
    counter++;
  } else { // Stopped on a specific potentiometer
    note = map(analogRead(pattern), 0, 1023, lowFreq, highFreq);
    if (note > lowFreq + 10) {
      tone(speaker, note);
    } else {
      noTone(speaker);
    }
  }
}
