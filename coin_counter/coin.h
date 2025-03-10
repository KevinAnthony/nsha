#ifndef coin_h
#define coin_h

#include "Arduino.h" 
class Coin {
public:
  Coin(int value, mask);
  bool CheckSensor(uint16_t);
  bool CheckButton(uint16_t);
  char* String();
private:
  uint8_t _mask;
  int _lastState;
  int _value;
  int _count;
  char _buffer[20];
};
#endif