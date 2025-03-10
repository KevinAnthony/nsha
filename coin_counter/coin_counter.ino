#include <Wire.h>
#include <pins_arduino.h>
#include "coin.h"
#include "MatrixOrbitali2c.h"

#define pulseWidth 5
#define inputWidth 8

#define QMask 1
#define DMask 2
#define NMask 4
#define PMask 8
#define UPBtnMask 16
#define DnBtnMask 32

#define HSenMask 16


#define inputLoad A0
#define inputCE A1
#define inputData A2
#define inputClock A3

#define outputLatch 2
#define outputClock 3
#define outputData 4

#define motorRunDelay 3000

Coin _q(10, 25);
Coin _d(7, 10);
Coin _n(9, 5);
Coin _p(8, 1);
Coin _selected;

unsigned long _elapsed = 0;

MatrixOrbitali2c screen(0x28);


/**************** INPUT ****************/

uint16_t readInput() {
  uint16_t result;
  digitalWrite(inputLoad, LOW);
  delayMicroseconds(pulseWidth);
  digitalWrite(inputLoad, HIGH);
  delayMicroseconds(pulseWidth);

  digitalWrite(inputClock, HIGH);
  digitalWrite(inputCE, LOW);
  byte button = shiftIn(inputData, inputClock, MSBFIRST);
  byte sensor = shiftIn(inputData, inputClock, MSBFIRST);
  digitalWrite(inputCE, HIGH);

  return sensor << 8 | button;
}

void processCoinInput(uint16_t input) {
  readLaneSesnor(_q, input);
  readButton(_q, input);

  readLaneSesnor(_d, input);
  readButton(_d, input);

  readLaneSesnor(_n, input);
  readButton(_n, input);

  readLaneSesnor(_p, input);
  readButton(_p, input);
}

void readLaneSesnor(Coin c, uint16_t input) {
  if (c.CheckSensor(input)) {
    _elapsed = millis();
    Serial.println(c->String());
  }
}

void readButton(Coin c, uint16_t input) {
  if (c.CheckButton(input)) {
    _selected = c
  })
}

/**************** OUTPUT ****************/

void refreshDisplay() {
  size_t err;
  err = screen.write(_q.String());
  if (err > 0) {
    // if we can't write to the screen, turn it off and re-initize.  this usally means the cpu came up before the VFD was done booting
    Wire.end();
    delay(10);
    screen.begin(4, 20);
    return;
  }

  screen.write(_d.String());
  screen.write(_n.String());
  screen.write(_p.String());
}

void putOutput(uint8_t data) {
  digitalWrite(outputLatch, LOW);
  shiftOut(outputData, outputClock, LSBFIRST, data);
  digitalWrite(outputLatch, HIGH);
}

/**************** ARDUINO ****************/

void setup() {
  Serial.begin(9600);

  screen.begin(4, 20);

  _selected = _q;
  pinMode(inputLoad, OUTPUT);
  pinMode(inputCE, OUTPUT);
  pinMode(inputData, INPUT);
  pinMode(inputClock, OUTPUT);

  pinMode(outputLatch, OUTPUT);
  pinMode(outputClock, OUTPUT);
  pinMode(outputData, OUTPUT);
}

void loop() {
  uint8_t input = readInput();
  processCoinInput(input);

  

  Serial.println(input, BIN);

  putOutput(selectedButton);

  // refreshDisplay();

  // if (_elapsed > 0 && millis() - _elapsed > motorRunDelay) {
  //   _elapsed = 0;
  // }
}
