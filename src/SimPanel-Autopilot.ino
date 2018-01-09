/*
* Project SimPanel-Autopilot
* Description: Autopilot module for Link2FS
* Author: mhespenh
* Date: 06 Jan 2018
*/
#include <libs/Switch.h>
#include <libs/Button.h>
#include <libs/Encoder.h>
#include <libs/Indicator.h>

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
// Components
Button button_autopilotMaster(RX);
Button button_autopilotHeadingHold(TX);
Button button_autopilotAltitudeHold(D0, false); // D0 is non interrupt-capable
Button button_autopilotNavHold(A1, false); // D7 is non interrupt-capable
Button button_autopilotAirspeedHold(A0, false); // A0 is non interrupt-capable

Encoder enc_autopilotHeading(D1, D2);
Encoder enc_autopilotAltitude(D3, D4);
Encoder enc_autopilotAirspeed(D5, D6);
Encoder enc_autopilotVerticalSpeed(A2, WKP);

Indicator ind_autopilotMaster(D7);
Indicator ind_autopilotHeadingHold(A3);
Indicator ind_autopilotAltitudeHold(A4);
Indicator ind_autopilotNavHold(A5);
Indicator ind_autopilotAirspeedHold(DAC);

String messageBuffer;
Message message;

void setup() {
// WiFi.off();        //Turn off wifi
 Serial.begin(115200);
 message = { false, false, '-', '-', String("") };
}

void loop() {
   handleButtons();
   handleSwitches();
   handleEncoders();

   if( message.isReady ) {
     message.isUnread = false;
     message.isReady = false;
     handleMessage();
   }
}

void handleEncoders() {
  if( enc_autopilotHeading.hasChanged() ) {
    if( enc_autopilotHeading.getUpdatedDirection() > 0 ) {
      Serial.println("A57"); //Increment heading hold value
    }
    else {
      Serial.println("A58"); //Decrement heading hold value
    }
  }
  if( enc_autopilotAltitude.hasChanged() ) {
    if( enc_autopilotAltitude.getUpdatedDirection() > 0 ) {
      Serial.println("B11"); //Increment altitude hold value
    }
    else {
      Serial.println("B12"); //Decrement altitude hold value
    }
  }
  if( enc_autopilotVerticalSpeed.hasChanged() ) {
    if( enc_autopilotVerticalSpeed.getUpdatedDirection() > 0 ) {
      Serial.println("B13"); //Increment vertical speed hold value
    }
    else {
      Serial.println("B14"); //Decrement vertical speed hold value
    }
  }
  if( enc_autopilotAirspeed.hasChanged() ) {
    if( enc_autopilotAirspeed.getUpdatedDirection() > 0 ) {
      Serial.println("B15"); //Increment airspeed hold value
    }
    else {
      Serial.println("B16"); //Decrement airspeed hold value
    }
  }
}

void handleButtons() {
  if( button_autopilotMaster.wasPressed() ) {
     Serial.println("B01"); //toggle autopilot master
   }
  if( button_autopilotHeadingHold.wasPressed() ) {
    Serial.println("B04"); //toggle autopilot heading hold
  }
  if( button_autopilotAltitudeHold.wasPressed() ) {
   Serial.println("B05"); //toggle altitude hold
  }
  if( button_autopilotNavHold.wasPressed() ) {
    Serial.println("B10"); //toggle autopilot nav hold
  }
  if( button_autopilotAirspeedHold.wasPressed() ) {
     Serial.println("B26"); //toggle autopilot airspeed hold
   }
}

void handleSwitches() {
  // we don't have any switches
}

void handleMessage() {
//  Serial.printlnf("Got message CMD: '%c', Letter: %c, data: %s", message.cmd, message.letter, message.data.c_str());
  switch( message.cmd ) {
    case '=':
      switch( message.letter ) {
        // Indicators
        case 'a':
          message.data.toInt() == 1 ? ind_autopilotMaster.on() : ind_autopilotMaster.off();
          break;
        case 'j':
          message.data.toInt() == 1 ? ind_autopilotHeadingHold.on() : ind_autopilotHeadingHold.off();
          break;
        case 'k':
          message.data.toInt() == 1 ? ind_autopilotAltitudeHold.on() : ind_autopilotAltitudeHold.off();
          break;
        case 'o':
          message.data.toInt() == 1 ? ind_autopilotNavHold.on() : ind_autopilotNavHold.off();
          break;
        case 's':
          message.data.toInt() == 1 ? ind_autopilotAirspeedHold.on() : ind_autopilotAirspeedHold.off();
          break;
      }
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
