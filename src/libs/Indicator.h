#ifndef Indicator_h
#define Indicator_h

class Indicator {
  public:
    Indicator(int);
    void on();
    void off();
    void toggle();
    bool isOn();
  private:
    int _state;
    int _pin;
};

#endif