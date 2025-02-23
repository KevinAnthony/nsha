#include "lanesensor.h"

LaneSensor* _q;
LaneSensor* _d;
LaneSensor* _n;
LaneSensor* _p;
unsigned long elapsed = 0;
unsigned long RunDelay  = 3000;

void check(LaneSensor* c) {
  if (c->CheckCount()) {
    elapsed = millis();
    Serial.println(c->String());
  }
}

void setup() {
  Serial.begin(9600);
  _q = new LaneSensor(10, 25);
  _d = new LaneSensor(7, 10);
  _n = new LaneSensor(9, 5);
  _p = new LaneSensor(8, 1);
}

void loop() {
  check(_q);
  check(_n);
  check(_p);
  check(_d);

  if (elapsed > 0 && millis() - elapsed > RunDelay) {
    elapsed = 0;
  }
}

