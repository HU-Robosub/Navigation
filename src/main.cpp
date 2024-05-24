#include "Common.h"
#include "Mpu6050.h"
#include "Lsm303.h"
#include "SlaveI2C.h"

// Mpu6050 sensor, used for accelerometer and gyroscope
Mpu6050 mpu6050;

// Lsm303 sensor, used for compass
Lsm303 lsm303;

// SlaveI2C object
SlaveI2C slave;

void setup()
{
  Serial.begin(9600);
  while(!Serial) {
    delay(1000); // Wait until serial console opens
  }

  // Initialize the SlaveI2C with default address 0
  slave.begin(0);

  // Initialize LSM303 compass
  lsm303.begin();

  // Initialize MPU6050
  if (!mpu6050.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while(1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  // Setup MPU6050
  mpu6050.setupMPU6050();
  Serial.println("");
  delay(100);
}

void loop()
{
  // Read compass data
  lsm303.readCompass();

  // Calculate and print the heading
  float heading = lsm303.getHeading();
  Serial.print("Heading: ");
  Serial.println(heading);

  // Print MPU6050 data
  mpu6050.printMPU6050Data();

  delay(500);
}