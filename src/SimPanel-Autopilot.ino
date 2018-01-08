/*
* Project SimPanel-Autopilot
* Description: Autopilot module for Link2FS
* Author: mhespenh
* Date: 06 Jan 2018
*/
#include "pins.h"
#include <libs/Indicator.h>
#include <libs/Button.h>
#include <libs/Encoder.h>

// Photon specific-- disable cloud connection
//  otherwise setup and loop won't run
//SYSTEM_MODE(MANUAL);

// Globals
volatile bool buttonsChanged;
Button b(A0);
Indicator i(D0);

// Don't use D0 or A5 for interrupts!
Encoder e(D4,D6);
long oldPos;

void setup() {
// WiFi.off();        //Turn off wifi
 Serial.begin(115200);
 pinMode(D5, OUTPUT);
 pinMode(D1, OUTPUT);
 digitalWrite(D1, LOW);
 digitalWrite(D5, LOW);
 Serial.println("Ready");
}

void loop() {
 if( b.wasPressed() ) {
   Serial.println("Pressed! ");
   Serial.println(millis());
   i.toggle();
 }

 long pos = e.read();
 if( pos != oldPos ) {
   oldPos = pos;
   Serial.println(pos);
 }
}

void EQUALS(){      // The first identifier was "="
  char CodeIn = Serial.read(); // Get the second identifier
  switch(CodeIn) {// Now lets find what to do with it
  case 'A'://Found the second identifier
      //Do something
   break;

   case 'B':
      //Do something
   break;

   case 'C':
      //Do something
   break;

        //etc etc etc
  }
}

void LESSTHAN(){    // The first identifier was "<"
  char CodeIn = Serial.read(); // Get the second identifier
  switch(CodeIn) {// Now lets find what to do with it
   case 'A'://Found the second identifier "GearN"
   break;

   case 'B':
   break;

   case 'C':
   break;

      //etc etc etc
  }
}

void QUESTION(){    // The first identifier was "?"
  char CodeIn = Serial.read(); // Get the second identifier
  switch(CodeIn) {// Now lets find what to do with it
    case 'A'://Found the second identifier
      //Do something
      break;

    case 'B':
      //Do something
      break;

    case 'C':
      //Do something
      break;
    }
}

// Called automagically when serial data is ready
void serialEvent() {
  char code = Serial.read();
  if (code == '=') { EQUALS(); } // The first identifier is "="
  if (code == '<') { LESSTHAN(); }// The first identifier is "<"
  if (code == '?') { QUESTION(); }// The first identifier is "?"
//  if (code == '/') { SLASH(); }// The first identifier is "/" (Annunciators)
}
