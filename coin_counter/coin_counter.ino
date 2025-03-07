#include <Wire.h>
#include "lanesensor.h"
#include "MatrixOrbitali2c.h"
#include "ShiftIn.h"

int buttonLoad = 19;
int buttonCE = 20;
int buttonData = 21;
int buttonClock = 22;

LaneSensor _q(10, 25);
LaneSensor _d(7, 10);
LaneSensor _n(9, 5);
LaneSensor _p(8, 1);
unsigned long elapsed = 0;
unsigned long RunDelay = 3000;
ShiftIn<1> shift;
MatrixOrbitali2c lcd(0x28);

void check(LaneSensor* c) {
  if (c->CheckCount()) {
    elapsed = millis();
    Serial.println(c->String());
  }
}

void refreshDisplay() {
  size_t err;
  err = lcd.write(_q.String());
  if (err > 0) {
    Serial.println("error");
    Wire.end();
    delay(10);
    lcd.begin(4, 20);
    return;
  }

  lcd.write(_d.String());
  lcd.write(_n.String());
  lcd.write(_p.String());
}

void setup() {
  lcd.begin(4, 20);
  Serial.begin(9600);

  shift.begin(buttonLoad, buttonCD, buttonData, buttonClock);
}

void loop() {

  if (shift.update()) {  // read in all values. returns true if any button has changed
    for (int i = 0; i < shift.getDataWidth(); i++)
      Serial.print(shift.state(i));  // get state of button i
    Serial.println();
  }

  delay(1);
  // check(_q);
  // check(_n);
  // check(_p);
  // check(_d);

  // refreshDisplay();

  // if (elapsed > 0 && millis() - elapsed > RunDelay) {
  //   elapsed = 0;
  // }
}
