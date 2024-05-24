#include "SlaveI2C.h"

byte SlaveI2C::slaveAddress = 0;

SlaveI2C::SlaveI2C() {}

void SlaveI2C::begin(byte defaultAddress) {
    slaveAddress = defaultAddress;
    Wire.begin(slaveAddress); // Initialize with default address
    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);
}

void SlaveI2C::receiveEvent(int howMany) {
    if (howMany > 0) {
        byte received = Wire.read();
        if (slaveAddress == 0) {
            slaveAddress = received;
            Wire.begin(slaveAddress); // Change to the new address
        }
    }
}

void SlaveI2C::requestEvent() {
    Wire.write("Hello Master");
}