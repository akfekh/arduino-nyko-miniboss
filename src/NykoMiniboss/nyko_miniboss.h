#ifndef __NYKO_MINIBOSS_H__
#define __NYKO_MINIBOSS_H__
#define MINIBOSS_IDENTITY_BUFFER_SIZE 6
#define MINIBOSS_BUFFER_SIZE 8
#define MINIBOSS_I2C_ID 0x52
#define MB_ERROR_UNABLE_TO_INIT 1
#define MB_ERROR_

class NykoMiniboss {
  public:
    bool initialize();
    bool update();
    uint16_t getButtonState();

  private:
    void requestData();
    bool requestControllerIdentity(byte* identityBuffer);
    byte _buffer[MINIBOSS_BUFFER_SIZE];
};

#endif

