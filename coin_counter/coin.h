#ifndef coin_h
#define coin_h

#include "Arduino.h" 
class Coin {
public:
  Coin(int pin, int value);
  bool CheckCount();
  char* String();
private:
  int _lastState;
  int _pin;
  int _value;
  int _count;
  char _buffer[20];
};
#endif