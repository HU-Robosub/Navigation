#include <Arduino.h>
#include <Wire.h>

#define SLAVE_ADDRESS 5

volatile int reg;

// int accel_data[3] = {
//   10,
//   20,
//   12
// };
void onReceiveEvent(int numBytes) {
  Serial.println("Recieved a byte!");
  while (Wire.available())
  {
    reg = Wire.read();
  }
  Serial.print("Register byte: ");
  Serial.println(reg);
  Serial.println("Receive processed!");
}

void onRequestEvent() {
  Serial.println("Recieved a request!");
  if (reg == 0) {
    Serial.println("Writing 0!");
    Wire.write(0);
  }
  else if (reg == 1) {
    Serial.println("Writing 1!");
    Wire.write(1);
  }
  else if (reg == 2) {
    Serial.println("Writing 2!");
    Wire.write(2);
  }
  else {
    Serial.println("Writing 3!");
    Wire.write(3);
  }
  Serial.println("");
}

void setup() {
  Wire.begin(SLAVE_ADDRESS);
  Serial.begin(9600);
  while (!Serial)
  {
    delay(3000);
  }
  Serial.println("Initialized Serial");
  Wire.onRequest(onRequestEvent);
  Wire.onReceive(onReceiveEvent);
  Serial.println("Configured I2C");
}

void loop() {}
