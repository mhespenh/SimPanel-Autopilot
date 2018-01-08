#ifndef Button_h
#define Button_h

class Button {
  public:
    // Constructor takes a pin# and a pointer to the ISR
    Button(int);
    bool wasPressed(void);
  private:
    void _ISR();
    int _pin;
    int _isPressed;
    unsigned long _lastInterruptMillis;
};

#endif
