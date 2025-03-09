#include <Wire.h>
#include <pins_arduino.h>
#include "lanesensor.h"
#include "MatrixOrbitali2c.h"

#define pulseWidth 5
#define inputWidth 8

#define inputLoad A0
#define inputCE A1
#define inputData A2
#define inputClock A3

#define outputLatch 2
#define outputClock 3
#define outputData 4

#define motorRunDelay 3000

LaneSensor _q(10, 25);
LaneSensor _d(7, 10);
LaneSensor _n(9, 5);
LaneSensor _p(8, 1);

unsigned long elapsed = 0;

MatrixOrbitali2c screen(0x28);


void readLaneSesnor(LaneSensor* c) {
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

uint8_t readInput() {
  uint8_t result;
  digitalWrite(inputLoad, LOW);
  delayMicroseconds(pulseWidth);
  digitalWrite(inputLoad, HIGH);
  delayMicroseconds(pulseWidth);

  digitalWrite(inputClock, HIGH);
  digitalWrite(inputCE, LOW);
  byte incoming = shiftIn(inputData, inputClock, LSBFIRST);
  digitalWrite(inputCE, HIGH);

  return incoming;
}

void putOutput(uint8_t data ) {
  digitalWrite(outputLatch, LOW);
  shiftOut(outputData, outputClock, LSBFIRST, data);
  digitalWrite(outputLatch, HIGH);
}

void loop() {
  uint8_t input = readInput();
  //TODO decode input here
  Serial.println(input, BIN);

  putOutput(input);

  // readLaneSesnor(_q);
  // readLaneSesnor(_n);
  // readLaneSesnor(_p);
  // readLaneSesnor(_d);

  // refreshDisplay();

  // if (elapsed > 0 && millis() - elapsed > motorRunDelay) {
  //   elapsed = 0;
  // }
}
