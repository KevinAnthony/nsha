#ifndef lanesensor_h
#define lanesensor_h

#include "Arduino.h" 
class LaneSensor {
public:
  LaneSensor(int pin, int value);
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