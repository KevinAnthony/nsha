#include "Arduino.h"
#include "coin.h"
#include <math.h>

Coin::Coin(int value, mask uint8_t) {
  _lastState = HIGH;
  _count = 0;

  _mask = mask;
  _value = value;

  pinMode(_pin, INPUT);
  digitalWrite(_pin, HIGH);
}

bool Coin::CheckSesnor(input uint16_t) {
  bool laneState = (input>>8 & _mask) == _mask;

  if (!laneState && _lastState) {
    _count++;
    _lastState = curState;

    return true;
  }

  _lastState = curState;

  return false;
}

bool Coin::CheckButton(input uint16_t){
    bool btnState = (input & _mask) == _mask;

    return false;
}

char* Coin::String() {
  double value = (_value * _count) / 100.0;
  double whole, fraction;

  fraction = modf(value, &whole) * 100;
  sprintf(_buffer, "0.%02d - % 4d $% 4d.%02d", _value, _count, int(whole), int(fraction));

  return _buffer;
}