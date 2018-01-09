#ifndef GearIndicator_h
#define GearIndicator_h

#include "Indicator.h"

class GearIndicator {
  public:
    GearIndicator(int, int);
    void parseUpdate(int);

  private:
    void _setDownLocked();
    void _setStowed();
    void _setInTransit();

    Indicator _redIndicator;
    Indicator _greenIndicator;
};

#endif
