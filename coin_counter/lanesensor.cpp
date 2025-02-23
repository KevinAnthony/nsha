#include "Arduino.h"
#include "lanesensor.h"
#include <math.h>

LaneSensor::LaneSensor(int pin, int value) {
  _lastState = HIGH;
  _count = 0;
  _pin = pin;
  _value = value;

  pinMode(_pin, INPUT);
  digitalWrite(_pin, HIGH);
}

bool LaneSensor::CheckCount() {
  int curState = digitalRead(_pin);

  if (!curState && _lastState) {
    Serial.print(curState);
    Serial.print(" ");
    Serial.print(_lastState);
    Serial.print(" ");
    Serial.println(_count);

    _count++;
    _lastState = curState;

    Serial.print(curState);
    Serial.print(" ");
    Serial.print(_lastState);
    Serial.print(" ");
    Serial.println(_count);

    return true;
  }

  _lastState = curState;

  return false;
}

char* LaneSensor::String() {
  double value = (_value * _count) / 100.0;
  double whole, fraction;

  fraction = modf(value, &whole) * 100;
  sprintf(_buffer, "0.%02d - % 4d $% 4d.%02d", _value, _count, int(whole), int(fraction));

  return _buffer;
}