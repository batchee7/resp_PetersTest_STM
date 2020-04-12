#ifndef K30_H
#define K30_H
 
#include "mbed.h"

class K30 {
public:
    K30(PinName sda, PinName scl, char add);
    bool readCo2();
    bool readStatus();
    bool disableABC();
    uint16_t CO2() {return _co2;}
    char Status() {return _status;}
    
private:
    I2C _i2c;
    uint8_t _i2caddr;
    uint16_t  _co2;
    char _status;
};


#endif