#ifndef SLAVEI2C_H
#define SLAVEI2C_H

#include <Arduino.h>
#include <Wire.h>

class SlaveI2C {
public:
    SlaveI2C();
    void begin(byte defaultAddress);
    static void receiveEvent(int howMany);
    static void requestEvent();

private:
    static byte slaveAddress;
};

#endif