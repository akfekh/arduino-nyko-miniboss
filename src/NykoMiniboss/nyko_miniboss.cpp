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
  
  update();
  return true;
}

/* Button codes returned from this method(hex provided for convenience)
 *        -----BINARY------ --HEX-
 * UP     00000000 00000001 0x0001
 * LEFT   00000000 00000010 0x0002
 * A      00000000 00010000 0x0010
 * B      00000000 01000000 0x0040
 * START  00000100 00000000 0x0400
 * POWER  00001000 00000000 0x0800
 * SELECT 00010000 00000000 0x1000
 * DOWN   01000000 00000000 0x4000
 * RIGHT  10000000 00000000 0x8000
 */
uint16_t NykoMiniboss::getButtonState() {
  return ~((_buffer[6] << 8) | _buffer[7]);
}

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
  Wire.requestFrom(MINIBOSS_I2C_ID, MINIBOSS_BUFFER_SIZE);
  byte bytesRead = 0;
  while(Wire.available() && bytesRead < MINIBOSS_BUFFER_SIZE) {
    _buffer[bytesRead] = Wire.read();
    bytesRead++;
  }
  requestData();
  return bytesRead == MINIBOSS_BUFFER_SIZE;
}

