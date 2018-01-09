#include "Switch.h"
#include "Particle.h"

Switch::Switch(int pin) {
  this->_pin = pin;
  pinMode(pin, INPUT_PULLDOWN);
  attachInterrupt(pin, &Switch::_ISR, this, CHANGE);
}

bool Switch::getState() {
  return this->_state;
}

bool Switch::isChanged() {
  if( this->_isChanged) {
    this->_isChanged = false;
    return true;
  }

  return false;
}

void Switch::_ISR() {
  this->_state = digitalRead(this->_pin);
  this->_isChanged = true;
}
