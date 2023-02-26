/*
 * Code originally from 
 * https://create.arduino.cc/projecthub/eEdizon/arduino-step-sequencer-afea0e
 * https://www.hackster.io/eEdizon/arduino-step-sequencer-afea0e
 * Licensed under © GPL3+
 * 
 * Project originally from 
 * https://makeyouruno.arduino.cc/makeyouruno/module/projects/lesson/04-make-your-synth-shield
 * 
 * This is an updated version of the projects listed above. 
 * An assembled synth must be horizontally oriented, like this: [:::O]
 * The four knobs on the left adjust audio frequencies, one note each (connected to A0-A3).
 * The top right potentiometer adjusts the volume of the speaker (connected to D9).
 * The bottom right potentiometer adjusts the arpeggiator tempo (connected to A4).
 */

const byte speaker = 9;       // Speaker pin
const bool debug = false;     // Set to True to print values to Serial Monitor
const short lowFreq = 10;     // The lower frequency boundary
const short highFreq = 2000;  // The higher frequency boundary
short counter = 0;            // Used for speed
short tempo = 0;              // Used for reading the speed
byte pattern = 0;             // Current potentiometer
short note = 0;               // Note that will be played

short getNote(byte pattern) {  
  // Get notes for specific patterns
  note = map(analogRead(pattern+14), 0, 1023, lowFreq, highFreq);
  return note;
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  tempo = map(analogRead(A4), 0, 1023, 4000, 100);  // Reverse mapping
  if (tempo < 3900) {                               // Enter if speed still acceptable
    if(counter > tempo) {
      if(debug) {
        Serial.println(pattern);
      }
      noTone(speaker);
      note = getNote(pattern);
      if(note > lowFreq + 10) {
        tone(speaker, note);
      }
      counter = 0;
      pattern = (pattern + 1) % 4;
    }
    counter++;
  } else {                      // Stopped on a specific potentiometer
    note = getNote(pattern);
    if (note > lowFreq + 10) {
      tone(speaker, note);
    } else {
      noTone(speaker);
    }
  }
}
