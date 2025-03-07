#include <Wire.h>
#include "lanesensor.h"
#include "MatrixOrbitali2c.h"

LaneSensor _q(10,25);
LaneSensor _d(7,10);
LaneSensor _n(9,5);
LaneSensor _p(8,1);
unsigned long elapsed = 0;
unsigned long RunDelay  = 3000;
MatrixOrbitali2c lcd(0x28);

void check(LaneSensor* c) {
  if (c->CheckCount()) {
    elapsed = millis();
    Serial.println(c->String());
  }
}

void refreshDisplay(){
  size_t err;
  err = lcd.write(_q.String());
  if (err > 0) {
    Serial.println("error");
    Wire.end();
    delay(10);
    lcd.begin(4,20);
    return;
  }
  
  lcd.write(_d.String());
  lcd.write(_n.String());
  lcd.write(_p.String());
}

void setup() {
  lcd.begin(4,20);
  Serial.begin(9600);
}

void loop() {
  // check(_q);
  // check(_n);
  // check(_p);
  // check(_d);

  refreshDisplay();

  // if (elapsed > 0 && millis() - elapsed > RunDelay) {
  //   elapsed = 0;
  // }
}

