#ifndef LSM303_H
#define LSM303_H

#include <Arduino.h>
#include <Wire.h>
#include <LSM303.h>

class Lsm303 {
  public:
    Lsm303();
    void begin();
    void readCompass();
    float getHeading();

  private:
    LSM303 compass;
    LSM303::vector<int16_t> running_min;
    LSM303::vector<int16_t> running_max;
};

#endif