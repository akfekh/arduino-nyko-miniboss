#ifndef __NYKO_MINIBOSS_H__
#define __NYKO_MINIBOSS_H__
#define MINIBOSS_IDENTITY_BUFFER_SIZE 6
#define MINIBOSS_BUFFER_SIZE 8
#define MINIBOSS_I2C_ID 0x52

class NykoMiniboss {
  public:
    bool initialize();
    bool update();
//    void print();
    bool isPressingA();
    bool isPressingB();
    bool isPressingDown();
    bool isPressingLeft();
    bool isPressingPower();
    bool isPressingRight();
    bool isPressingSelect();
    bool isPressingStart();
    bool isPressingUp();

  private:
    void requestData();
    bool requestControllerIdentity(byte* identityBuffer);
    byte _buffer[MINIBOSS_BUFFER_SIZE];
};

#endif

