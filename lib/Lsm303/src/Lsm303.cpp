#include "Lsm303.h"

Lsm303::Lsm303() : running_min({32767, 32767, 32767}), running_max({-32768, -32768, -32768}) {}

void Lsm303::begin() {
  Wire.begin();
  compass.init();
  compass.enableDefault();

  // Set initial calibration values; these should be updated using the calibration routine
  compass.m_min = (LSM303::vector<int16_t>){-32767, -32767, -32767};
  compass.m_max = (LSM303::vector<int16_t>){+32767, +32767, +32767};
}

void Lsm303::readCompass() {
  compass.read();

  // Update running minimum and maximum values for calibration
  running_min.x = min(running_min.x, compass.m.x);
  running_min.y = min(running_min.y, compass.m.y);
  running_min.z = min(running_min.z, compass.m.z);

  running_max.x = max(running_max.x, compass.m.x);
  running_max.y = max(running_max.y, compass.m.y);
  running_max.z = max(running_max.z, compass.m.z);
}

float Lsm303::getHeading() {
  // Calculate offset and scale values from calibration data
  LSM303::vector<float> mag_offset = {
    static_cast<float>((running_min.x + running_max.x) / 2.0),
    static_cast<float>((running_min.y + running_max.y) / 2.0),
    static_cast<float>((running_min.z + running_max.z) / 2.0)
  };
  
  LSM303::vector<float> mag_scale = {
    static_cast<float>((running_max.x - running_min.x) / 2.0),
    static_cast<float>((running_max.y - running_min.y) / 2.0),
    static_cast<float>((running_max.z - running_min.z) / 2.0)
  };

  // Apply calibration to raw data
  float x = (compass.m.x - mag_offset.x) / mag_scale.x;
  float y = (compass.m.y - mag_offset.y) / mag_scale.y;
  float z = (compass.m.z - mag_offset.z) / mag_scale.z;

  // Calculate heading
  float heading = atan2(y, x) * 180 / PI;
  if (heading < 0) {
    heading += 360;
  }

  return heading;
}