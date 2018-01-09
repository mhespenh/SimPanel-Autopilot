#ifndef Switch_h
#define Switch_h

#define SPST 0
#define SPDT 1

class Switch {
  public:
    Switch(int);
    bool getState();
    bool isChanged();

  private:
    void _ISR();
    int _pin;
    int _state;
    bool _isChanged;
};

#endif
