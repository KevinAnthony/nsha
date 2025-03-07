#ifndef VFD_h
#define VFD_h



#include <inttypes.h>
// #include "Arduino.h"
#include <Wire.h>

// Command character

#define MO_COMMANDCHAR 0xFE

// Display commands
#define MO_CLEARDISPLAY 0x58
#define MO_HOME 0x48
#define MO_AUTOSCROLLON 0x51
#define MO_AUTOSCROLLOFF 0x52
#define MO_LINEWRAPON 0x43
#define MO_LINEWRAPOFF 0x44
#define MO_SETCURSORPOS 0x47

// Cursor commands
#define MO_CURSORON 0x4A
#define MO_CURSOROFF 0x4B
#define MO_CURSORBLINKON 0x53
#define MO_CURSORBLINKOFF 0x54

#define MO_CURSORLEFT 0x4C
#define MO_CURSORRIGHT 0x4D

#endif

class VFD {
  MatrixOrbitali2c(uint8_t i2cport)
public:
   void begin();