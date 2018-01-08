#include "Particle.h"
#include "Indicator.h"

Indicator::Indicator(int pin) {
  pinMode(pin, OUTPUT);
  _pin = pin;
}

void Indicator::on() {
  digitalWrite(_pin, HIGH);
  this->_state = HIGH;
}

void Indicator::off() {
  digitalWrite(_pin, LOW);
  this->_state = LOW;
}

void Indicator::toggle() {
  digitalWrite(_pin, !this->_state);
  this->_state = !this->_state;
}

bool Indicator::isOn() {
  return this->_state;
}
