#include <Wire.h>
#include "nyko_miniboss.h"

const unsigned int BAUD_RATE = 19200;
NykoMiniboss miniboss;
bool initialized;

void setup() {
  Serial.begin(BAUD_RATE);
  initialized = miniboss.initialize();
}

void loop() {
  if (initialized) {
    delay(50);
    if (miniboss.update()) {
      Serial.println(miniboss.getButtonState());
    }
  } else {
    Serial.println("The controller was unable to initialize");
    delay(10000);
  }
}
