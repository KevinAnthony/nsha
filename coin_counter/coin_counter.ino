#include <Wire.h>
#include <pins_arduino.h>
#include "coin.h"
#include "MatrixOrbitali2c.h"

#define pulseWidth 5
#define inputWidth 8

#define QBtnMask 1
#define DBtnMask 2
#define NBtnMask 4
#define PBtnMask 8
#define UPBtnMask 16
#define DnBtnMask 32
#define CtrBtnOutMask 0xFF

#define QSenMask 256
#define DSenMask 512
#define NSenMask 1024
#define PSenMask 2048
#define HSenMask 4096


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

unsigned long elapsed = 0;

uint8_t selectedButton;

MatrixOrbitali2c screen(0x28);


void readLaneSesnor(Coin* c) {
  if (c->CheckCount()) {
    elapsed = millis();
    Serial.println(c->String());
  }
}

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

void setup() {
  Serial.begin(9600);

  // screen.begin(4, 20);

  pinMode(inputLoad, OUTPUT);
  pinMode(inputCE, OUTPUT);
  pinMode(inputData, INPUT);
  pinMode(inputClock, OUTPUT);

  pinMode(outputLatch, OUTPUT);
  pinMode(outputClock, OUTPUT);
  pinMode(outputData, OUTPUT);
}

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

void putOutput(uint8_t data) {
  digitalWrite(outputLatch, LOW);
  shiftOut(outputData, outputClock, LSBFIRST, data);
  digitalWrite(outputLatch, HIGH);
}

bool isActive(uint16_t input, uint16_t mask) {
  return (input & mask) == mask;
}

void processInput(uint16_t input) {
  if (isActive(input, QBtnMask)) {
    selectedButton = QBtnMask;
  }
  if (isActive(input, DBtnMask)) {
    selectedButton = DBtnMask;
  }
  if (isActive(input, NBtnMask)) {
    selectedButton = NBtnMask;
  }
  if (isActive(input, QBtnMask)) {
    selectedButton = PBtnMask;
  }
}

void loop() {
  uint8_t input = readInput();
  processInput(input);
  Serial.println(input, BIN);

  putOutput(selectedButton);

  // readLaneSesnor(_q);
  // readLaneSesnor(_n);
  // readLaneSesnor(_p);
  // readLaneSesnor(_d);

  // refreshDisplay();

  // if (elapsed > 0 && millis() - elapsed > motorRunDelay) {
  //   elapsed = 0;
  // }
}
