#include "vfd.h"
#include <Wire.h>

VFD::VFD(uint8_t i2cport) {
  _i2cport = i2cport;
}

void VFD::begin() {
  Wire.begin();
  clear();
  noBlink();
  noCursor();
  noAutoScroll();
  noLineWrap();
}

void VFD::clear() {
  write(MO_COMMANDCHAR);
  write(MO_CLEARDISPLAY);
}

void VFD::noBlink() {
  write(MO_COMMANDCHAR);
  write(MO_CURSORBLINKOFF);
}

void VFD::noCursor() {
  write(MO_COMMANDCHAR);
  write(MO_CURSOROFF);
}

void VFD::noAutoScroll() {
  write(MO_COMMANDCHAR);
  write(MO_AUTOSCROLLOFF);
}

void VFD::noLineWrap() {
  write(MO_COMMANDCHAR);
  write(MO_LINEWRAPOFF);
}

size_t VFD::write(uint8_t value) {
  Wire.beginTransmission(_i2cport);
  Wire.write(value);
  return Wire.endTransmission();
}

size_t VFD::write(const char *str) {
  Wire.beginTransmission(_i2cport);
  while (*str)
    Wire.write(*str++);
  return Wire.endTransmission();
}