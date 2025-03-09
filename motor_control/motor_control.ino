const int onButtonPin = 19;
const int offButtonPin = 20;
const int ledRelayPin = 15;

byte state = LOW;

ZUNO_SETUP_CHANNELS(ZUNO_SWITCH_BINARY(getter, setter));

void setup() {
  Serial.begin(9600);

  pinMode(ledRelayPin, OUTPUT);
  pinMode(onButtonPin, INPUT);
  pinMode(offButtonPin, INPUT);
  
  digitalWrite(ledRelayPin, state);

  ZUNO_SETUP_PRODUCT_AUTO()
}

void loop() {
  // put your main code here, to run repeatedly:
  byte onState = digitalRead(onButtonPin);
  byte offState = digitalRead(offButtonPin);

  if (state == HIGH && offState == LOW) {
    state = LOW;
  } else if (onState == HIGH) {
    state = HIGH;
  } else {
    return;
  }
    digitalWrite(ledRelayPin, state);
    delay(1000);
    zunoSendReport(1);
}

void setter(byte value) {
  Serial.println("setter called");
  // value is a variable, holding a "new value"
  // which came from the controller or other Z-Wave device
  if (value > 0) {               // if greater then zero
    digitalWrite (ledRelayPin, HIGH); //turn the LED on (HIGH is the voltage level)
    state = HIGH;
  } else {                         // if equals zero
    digitalWrite(ledRelayPin, LOW);   //turn the LED off by making the voltage LOW
    state = LOW;
  }
}

byte getter() {
  Serial.println("getter called");

  return state;
}