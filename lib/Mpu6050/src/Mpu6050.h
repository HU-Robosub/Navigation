#ifndef MPU6050_H
#define MPU6050_H

#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

class Mpu6050 {
  public:
    Mpu6050();
    bool begin();
    void setupMPU6050();
    void printMPU6050Data();

  private:
    Adafruit_MPU6050 mpu;
};

#endif