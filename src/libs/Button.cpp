#include "Particle.h"
#include "Button.h"

Button::Button(int pin) {
  pinMode(pin, INPUT_PULLDOWN);
  attachInterrupt(pin, &Button::_ISR, this, RISING);
  this->_pin = pin;
  this->_isPressed = false;
}

bool Button::wasPressed() {
  if( this->_isPressed ) {
    this->_isPressed = false;
    return true;
  }
  else {
    return false;
  }
}

void Button::_ISR(void) {
  unsigned long now = millis();
  if( now - this->_lastInterruptMillis > 200 ) {
    this->_isPressed = true;
  }
  this->_lastInterruptMillis = now;
}
