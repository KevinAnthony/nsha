#include "Arduino.h"
#include "coin.h"
#include <math.h>

Coin::Coin(int value, uint8_t mask) {
  _lastState = HIGH;
  _count = 0;
  _buttonPressCounter = 0;

  _mask = mask;
  _value = value;
}

bool Coin::CheckSensor(uint16_t input) {
  bool laneState = (input >> 8 & _mask) == _mask;

  if (!laneState && _lastState) {
    _count++;
    _lastState = laneState;

    return true;
  }

  _lastState = laneState;
  
  return false;
}

bool Coin::CheckButton(uint16_t input) {
  bool btnState = (input & _mask) == _mask;
  if (_buttonPressCounter > 0 && btnState) {
    _buttonPressCounter = millis();
  }

  if (_buttonPressCounter > 0 && millis() - _buttonPressCounter > ResetPressTime) {
    _count = 0;
  }

  return false;
}

uint8_t Coin::GetMask() {
  return _mask;
}

void Coin::Reset() {
  _count = 0;
}

char* Coin::String() {
  double value = (_value * _count) / 100.0;
  double whole, fraction;

  fraction = modf(value, &whole) * 100;
  sprintf(_buffer, "0.%02d - % 4d $% 4d.%02d", _value, _count, int(whole), int(fraction));

  return _buffer;
}

Coin& Coin::operator++() {
  _count++;

  return *this;
}

Coin Coin::operator++(int) {
  _count++;

  return *this;
}

Coin& Coin::operator--() {
  _count--;

  return *this;
}

Coin Coin::operator--(int) {
  _count--;

  return *this;
}