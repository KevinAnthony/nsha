#include <Wire.h>
#include <pins_arduino.h>
#include "coin.h"
#include "vfd.h"

#define pulseWidth 5
#define inputWidth 8

#define QMask 1
#define DMask 2
#define NMask 4
#define PMask 8
#define UpBtnMask 16
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
#define motorPin 6

Coin _q(25, QMask);
Coin _d(10, DMask);
Coin _n(5, NMask);
Coin _p(1, PMask);
Coin _selected = _q;

uint64_t _sensorElapsed = 0;
uint64_t _resetElapsed = 0;

VFD screen(0x28);

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

  result = ~~sensor << 8 | button;

  return result;
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
    // Turn On Mosfet
    _sensorElapsed = millis();
  }
}

void readButton(Coin c, uint16_t input) {
  if (c.CheckButton(input)) {
    _selected = c;
  }
}

/**************** OUTPUT ****************/

void refreshDisplay() {
  size_t err;
  err = screen.write(_q.String());
  if (err > 0) {
    // if we can't write to the screen, turn it off and re-initize.  this usally means the cpu came up before the VFD was done booting
    Wire.end();
    delay(10);
    screen.begin();
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

  screen.begin();

  _selected = _q;
  pinMode(inputLoad, OUTPUT);
  pinMode(inputCE, OUTPUT);
  pinMode(inputData, INPUT);
  pinMode(inputClock, OUTPUT);

  pinMode(outputLatch, OUTPUT);
  pinMode(outputClock, OUTPUT);
  pinMode(outputData, OUTPUT);

  pinMode(motorPin, OUTPUT);
}

void loop() {
  Serial.println();

  uint16_t input = readInput();
  processCoinInput(input);

  uint8_t upDownMask = 0 | input & UpBtnMask | input & DnBtnMask;

  if (upDownMask == UpBtnMask) {
    _selected++;
  }

  if (upDownMask == DnBtnMask) {
    _selected--;
  }

  if (_resetElapsed > 0 && upDownMask == 48) {
    if (millis() - _resetElapsed > ResetPressTime) {
      _q.Reset();
      _d.Reset();
      _n.Reset();
      _p.Reset();
    }
  } else {
    _resetElapsed = 0;
  }

  putOutput(_selected.GetMask() | upDownMask);

  delay(1000);
  refreshDisplay();

  if (_sensorElapsed > 0 && millis() - _sensorElapsed > motorRunDelay) {
    // Turn off mosfet

    _sensorElapsed = 0;
  }
  digitalWrite(motorPin, HIGH);
  delay(1000);
  digitalWrite(motorPin, LOW);
}
