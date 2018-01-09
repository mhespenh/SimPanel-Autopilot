#ifndef Button_h
#define Button_h

/*
 * There are two versions of Button, one that uses interrupts (preferred)
 * and one that is polling-based.  Theoretically it is possible that the polling-based
 * method can miss button presses, though in practice that is probably pretty rare,
 * that said I always prefer interrupts when available for fleeting inputs.
 * I only added the non-interrupt version because I ran out of interrupt-capable inputs.
 * Anway, use Button(int pin) for an interrupting button and Button(int pin, bool useInterrupts=false)
 * for the polling version.  Usage in loop() is the same.
 */
class Button {
  public:
    // Constructor takes a pin# and a bool
    Button(int, bool); // Don't use interrupts if second param is false
    Button(int); // Use interrupts
    bool wasPressed(void);
  private:
    void _ISR();
    int _pin;
    int _isPressed;
    bool _isAcknowledged;
    bool _useInterrupts;
    unsigned long _lastCheckedMillis;
};

class ButtonNonInterrupt {
  public:
    // Constructor takes a pin# and a pointer to the ISR
    ButtonNonInterrupt(int);
    bool wasPressed(void);
  private:
    void _ISR();
    int _pin;
    bool _isAcknowledged;
    unsigned long _lastCheckedMillis;
};

#endif
