/*
* Project SimPanel-Autopilot
* Description: Autopilot module for Link2FS
* Author: mhespenh
* Date: 06 Jan 2018
*/
#include "pins.h"
#include <libs/GearIndicator.h>
#include <libs/Switch.h>
#include <libs/Button.h>
#include <libs/Encoder.h>

// Photon specific-- disable cloud connection
//  otherwise setup and loop won't run
//SYSTEM_MODE(MANUAL);

struct Message {
  bool isReady;
  bool isUnread;
  char cmd;
  char letter;
  String data;
};

// Globals
Switch switch_gear(A0);
Button button_apHeading(A1);
GearIndicator gearIndicator_nose(D0, D1);
GearIndicator gearIndicator_left(D2, D3);
GearIndicator gearIndicator_right(D4, D5);

String messageBuffer;
Message message;

// Don't use D0 or A5 for interrupts!
Encoder e(D4,D6);
long oldPos;

void setup() {
// WiFi.off();        //Turn off wifi
 Serial.begin(115200);
 pinMode(D5, OUTPUT);
 digitalWrite(D5, LOW);
 Serial.println("Ready");
 message = { false, false, '-', '-', String("") };
}

void loop() {
  if( button_apHeading.wasPressed() ) {
     Serial.println("Toggling AP");
   }

   long pos = e.read();
   if( pos != oldPos ) {
     oldPos = pos;
     Serial.println(pos);
   }

   if( message.isReady ) {
     message.isUnread = false;
     message.isReady = false;
     handleMessage();
   }
}

void handleMessage() {
  Serial.printlnf("Got message CMD: '%c', Letter: %c, data: %s", message.cmd, message.letter, message.data.c_str());
  switch( message.cmd ) {
    case '<':
      switch( message.letter ) {
        case 'A':
          gearIndicator_nose.parseUpdate(message.data.toInt());
          break;
        case 'B':
          gearIndicator_left.parseUpdate(message.data.toInt());
          break;
        case 'C':
          gearIndicator_right.parseUpdate(message.data.toInt());
          break;
      }
      break;

      case '=':
        //do stuff
        break;
  }
}

// Called automagically when serial data is ready
void serialEvent() {
  char inChar;
  while( Serial.available() ) {
    inChar = (char)Serial.read();
    if( !message.isUnread ) {
      message.isUnread = true;
      messageBuffer.remove(0);
    }
    if( inChar == '\r'  ) {
      message.cmd = messageBuffer.charAt(0);
      message.letter = messageBuffer.charAt(1);
      message.data = messageBuffer.substring(2);
      message.isReady = true;
    }
    else {
      messageBuffer += inChar;
    }
  }
}
