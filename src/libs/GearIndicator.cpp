#include "GearIndicator.h"
#include "Indicator.h"

GearIndicator::GearIndicator(int redPin, int greenPin) {
  this->_redIndicator.init(redPin);
  this->_greenIndicator.init(greenPin);
}

void GearIndicator::parseUpdate(int state) {
  if( state >= 100 ) {
    this->_setDownLocked();
  }
  else if( state > 0 ) {
    this->_setInTransit();
  }
  else {
    this->_setStowed();
  }
}

void GearIndicator::_setStowed() {
  this->_redIndicator.off();
  this->_greenIndicator.off();
}

void GearIndicator::_setInTransit() {
  this->_redIndicator.on();
  this->_greenIndicator.off();
}

void GearIndicator::_setDownLocked() {
  this->_redIndicator.off();
  this->_greenIndicator.on();
}
