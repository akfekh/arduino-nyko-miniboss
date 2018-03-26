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
    if (miniboss.update()) {
//      miniboss.print();
      if(miniboss.isPressingUp()) { Serial.print('U'); } else { Serial.print(' '); }
      if(miniboss.isPressingDown()) { Serial.print('D'); } else { Serial.print(' '); }
      if(miniboss.isPressingLeft()) { Serial.print('L'); } else { Serial.print(' '); }
      if(miniboss.isPressingRight()) { Serial.print('R'); } else { Serial.print(' '); }
      if(miniboss.isPressingA()) { Serial.print('A'); } else { Serial.print(' '); }
      if(miniboss.isPressingB()) { Serial.print('B'); } else { Serial.print(' '); }
      if(miniboss.isPressingSelect()) { Serial.print('-'); } else { Serial.print(' '); }
      if(miniboss.isPressingStart()) { Serial.print('+'); } else { Serial.print(' '); }
      if(miniboss.isPressingPower()) { Serial.print('P'); } else { Serial.print(' '); }
      Serial.println();
    }
  } else {
    Serial.println("The controller was unable to initialize");
    delay(10000);
  }
}
