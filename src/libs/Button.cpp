#include "Particle.h"
#include "Button.h"

Button::Button(int pin, bool useInterrupts) {
  pinMode(pin, INPUT_PULLDOWN);
  if( useInterrupts ) {
    attachInterrupt(pin, &Button::_ISR, this, RISING);
  }
  this->_pin = pin;
  this->_useInterrupts = useInterrupts;
  this->_isPressed = false;
  this->_isAcknowledged = false;
}

Button::Button(int pin) {
  pinMode(pin, INPUT_PULLDOWN);
  attachInterrupt(pin, &Button::_ISR, this, RISING);
  this->_pin = pin;
  this->_useInterrupts = true;
  this->_isPressed = false;
  this->_isAcknowledged = false;
}

bool Button::wasPressed() {
  if( this->_useInterrupts ) {
    if( this->_isPressed ) {
      this->_isPressed = false;
      return true;
    }
    else {
      return false;
    }
  }
  else {
    // This is a little confusing, basically,
    //   if the button is pressed
    //   AND we haven't already registered this button press in loop()
    // The last part is because we might call this function 100 times from loop()
    // between when the user presses and releases the button, but we only want
    // to register one button press
    if( digitalRead(this->_pin) == HIGH ) {
      if( this->_isAcknowledged ) {
        return false;
      }
      else {
        this->_isAcknowledged = true;
        return true;
      }
    }
    else {
      this->_isAcknowledged = false;
      return false;
    }
  }
}

void Button::_ISR(void) {
  unsigned long now = millis();
  if( now - this->_lastCheckedMillis > 200 ) {
    this->_isPressed = true;
  }
  this->_lastCheckedMillis = now;
}
