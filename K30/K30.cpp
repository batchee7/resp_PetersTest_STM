
#include "K30.h"
#include "K30.h"
 
K30::K30(PinName sda, PinName scl, char add) : _i2c(sda, scl) {
    _i2caddr = (add << 1);
    _i2c.frequency(100000); //--100kbit
    }

bool K30::readStatus() {
    //-- Request Status Command
    
    char readbuffer[3];
    char writebuffer[4] = {0x21, 0x00, 0x1E, 0x3F};
    _i2c.write(_i2caddr, writebuffer , 4);
    
    // -- Wait 10ms for the sensor to process our command.
    // -- Waiting 10ms will ensure the data is properly written to RAM (sensors uconntroller does both comms and measurements)
    wait_ms(10);
    
    // -- Read Sequence (requested 1 bytes so need to take in 3 bytes: payload, checksum and command status byte)
    _i2c.read(_i2caddr, readbuffer, 3);

    if (readbuffer[0] == 0x00) return false;
    char sum = 0; 
    sum = readbuffer[0] + readbuffer[1];
    
    // -- If we get a match then return value else return 0
    if(sum == readbuffer[2])
    {
        _status = readbuffer[1];
        return true;
        }
    else
    {
        return false;
        }
}

// -- Returns 0 if error.
bool K30::readCo2()
{
    uint16_t co2_value = 0;  // We will store the CO2 value inside this variable.
    char writebuffer[4] = {0x22, 0x00, 0x08, 0x2A};
    // -- Write Sequence
    _i2c.write(_i2caddr, writebuffer, 4);

    // -- Waiting 10ms will ensure the data is properly written to RAM (sensors uconntroller does both comms and measurements)
    wait_ms(10);
    
    // -- Read Sequence (requested 2 bytes so need to take in 4 bytes: payload, checksum and command status byte)
    char readbuffer[4];
    _i2c.read(_i2caddr, readbuffer, 4);

    // -- Bitwise Read
    co2_value = 0;
    co2_value |= readbuffer[1] & 0xFF;
    co2_value = co2_value << 8;
    co2_value |= readbuffer[2] & 0xFF;

    // -- Generate checksum byte to compare to recieved byte (for error checking)
    char sum = 0; 
    sum = readbuffer[0] + readbuffer[1] + readbuffer[2];
    
    if (readbuffer[0]== 0) return false;
    
    // -- If we get a match then return value else return Not a Number
    if(sum == readbuffer[3])
    {
            _co2 = co2_value;
            return true;
        }
    else
    {
        return false;
        }
}

bool K30::disableABC() {

    char writeBuffer[6] = {0x12, 0x00, 0x40, 0x00, 0x00, 0x52};
    // -- Write Sequence  (Write to register 40)  
     _i2c.write(_i2caddr, writeBuffer, 6);
    
    // -- Wait 10ms for the sensor to process our command.
    // -- Waiting 10ms will ensure the data is properly written to RAM (sensors uconntroller does both comms and measurements)
    wait_ms(10);
    
    // -- Read Sequence (conformation message)
    char readBuffer[2] = {0, 0};    
    _i2c.read(_i2caddr, readBuffer, 2);
    if (readBuffer[0] != 0x11) return false;
    
    // -- As a double check read the register to see if ABCS period has been updated ot 0
    wait_ms(500); //-- Allow register time to update!
    char writeBuffer2[4]= {0x22, 0x00, 0x40, 0x52};
    _i2c.write(_i2caddr, writeBuffer2, 4);
    
    // -- Wait 10ms for the sensor to process our command.
    // -- Waiting 10ms will ensure the data is properly written to RAM (sensors uconntroller does both comms and measurements)
    wait_ms(10);  
    
    // -- Read Sequence (requested 4 bytes so need to take in 4 bytes: payload, checksum and command status byte)

    char buffer2[4] = {0, 0, 0, 0}; 
    _i2c.read(_i2caddr, buffer2, 4);

    // -- Generate checksum byte to compare to transmitted byte (for error checking)
    char sum = 0; 
    sum = buffer2[0] + buffer2[1] + buffer2[2];
    
    // -- If we get a match then return value else return 0
    if (sum != buffer2[3])return false;
    
    // -- Made it to here so just read value and see thats its defintly 0
    return ((buffer2[1] + buffer2[2]) == 0) ? true: false;
}