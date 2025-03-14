#ifndef coin_h
#define coin_h

#define ResetPressTime 5000

#include "Arduino.h"
class Coin {
public:
  Coin(int value, uint8_t mask);
  bool CheckSensor(uint16_t input);
  bool CheckButton(uint16_t input);
  Reset();
  Set(uint8_t value);
  uint8_t Get();
  char* String();
  uint8_t GetMask();
  //operators
  Coin& operator++();
  Coin operator++(int);
  Coin& operator--();
  Coin operator--(int);

private:
  uint64_t _buttonPressCounter;
  uint8_t _mask;
  bool _lastState;
  uint8_t _value;
  uint8_t _count;
  char _buffer[20];
};
#endif