#include <Arduino.h>
#include <Wire.h>
#include "nyko_miniboss.h"

bool NykoMiniboss::initialize() {
  Wire.begin();
  
  Wire.beginTransmission(MINIBOSS_I2C_ID);
  Wire.write((byte)0xF0); // sends memory address
  Wire.write((byte)0x55); // sends data
  if (Wire.endTransmission() != 0) { return false; }
  
  Wire.beginTransmission(MINIBOSS_I2C_ID);
  Wire.write((byte)0xFB); // sends memory address
  Wire.write((byte)0x00); // sends data
  if (Wire.endTransmission() != 0) { return false; }

  byte identityBuffer[MINIBOSS_IDENTITY_BUFFER_SIZE];
  if (!requestControllerIdentity(identityBuffer)) {
    return false;
  }
//  if(requestControllerIdentity(identityBuffer)) {
//    Serial.print("Identity=");
//    for (byte i = 0; i < MINIBOSS_IDENTITY_BUFFER_SIZE; i++) {
//      Serial.print(identityBuffer[i], HEX);
//      Serial.print(' ');
//    }
//    Serial.println();
//  } else {
//    Serial.println("ERROR: Unable to identify the controller");
//    return false;
//  }
  update();
  return true;
}

bool NykoMiniboss::isPressingA() { return !(_buffer[7] & 0x10); }
bool NykoMiniboss::isPressingB() { return !(_buffer[7] & 0x40); }
bool NykoMiniboss::isPressingDown() { return !(_buffer[6] & 0x40); }
bool NykoMiniboss::isPressingLeft() { return !(_buffer[7] & 0x02); }
bool NykoMiniboss::isPressingPower() { return !(_buffer[6] & 0x08); }
bool NykoMiniboss::isPressingRight() { return !(_buffer[6] & 0x80); }
bool NykoMiniboss::isPressingSelect() { return !(_buffer[6] & 0x10); }
bool NykoMiniboss::isPressingStart() { return !(_buffer[6] & 0x04); }
bool NykoMiniboss::isPressingUp() { return !(_buffer[7] & 0x01); }

//void NykoMiniboss::print() {
//  for(byte i = 0; i < MINIBOSS_BUFFER_SIZE; i++) {
//    Serial.print(_buffer[i], HEX);
//    Serial.print(' ');
//  }
//  Serial.println();
//}

/* identityBuffer must point to an Array of size MINIBOSS_IDENTITY_BUFFER_SIZE. */
bool NykoMiniboss::requestControllerIdentity(byte* identityBuffer) {
  Wire.beginTransmission(MINIBOSS_I2C_ID);
  Wire.write((byte)0xFA);
  if (Wire.endTransmission() != 0) { return false; }

  Wire.requestFrom(MINIBOSS_I2C_ID, MINIBOSS_IDENTITY_BUFFER_SIZE);
  for (byte i = 0; i < MINIBOSS_IDENTITY_BUFFER_SIZE; i++) {
    identityBuffer[i] = Wire.read();
  }
  return true;
}

void NykoMiniboss::requestData() {
  Wire.beginTransmission(MINIBOSS_I2C_ID);
  Wire.write((byte)0x00);
  Wire.endTransmission();
}

bool NykoMiniboss::update() {
  delay(100);
  Wire.requestFrom(MINIBOSS_I2C_ID, MINIBOSS_BUFFER_SIZE);
  byte bytesRead = 0;
  while(Wire.available() && bytesRead < MINIBOSS_BUFFER_SIZE) {
    _buffer[bytesRead] = Wire.read();
    bytesRead++;
  }
  requestData();
  return bytesRead == MINIBOSS_BUFFER_SIZE;
}

