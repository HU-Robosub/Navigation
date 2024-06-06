// #include "Mpu6050.h"

// Mpu6050::Mpu6050() : mpu() {}

// bool Mpu6050::begin() {
//   return mpu.begin();
// }

// void Mpu6050::setupMpu6050() {
//   mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
//   Serial.print("Accelerometer range set to: ");
//   switch (mpu.getAccelerometerRange()) {
//     case MPU6050_RANGE_2_G:
//       Serial.println("+-2G");
//       break;
//     case MPU6050_RANGE_4_G:
//       Serial.println("+-4G");
//       break;
//     case MPU6050_RANGE_8_G:
//       Serial.println("+-8G");
//       break;
//     case MPU6050_RANGE_16_G:
//       Serial.println("+-16G");
//       break;
//   }

//   mpu.setGyroRange(MPU6050_RANGE_500_DEG);
//   Serial.print("Gyro range set to: ");
//   switch (mpu.getGyroRange()) {
//     case MPU6050_RANGE_250_DEG:
//       Serial.println("+- 250 deg/s");
//       break;
//     case MPU6050_RANGE_500_DEG:
//       Serial.println("+- 500 deg/s");
//       break;
//     case MPU6050_RANGE_1000_DEG:
//       Serial.println("+- 1000 deg/s");
//       break;
//     case MPU6050_RANGE_2000_DEG:
//       Serial.println("+- 2000 deg/s");
//       break;
//   }

//   mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
//   Serial.print("Filter bandwidth set to: ");
//   switch (mpu.getFilterBandwidth()) {
//     case MPU6050_BAND_260_HZ:
//       Serial.println("260 Hz");
//       break;
//     case MPU6050_BAND_184_HZ:
//       Serial.println("184 Hz");
//       break;
//     case MPU6050_BAND_94_HZ:
//       Serial.println("94 Hz");
//       break;
//     case MPU6050_BAND_44_HZ:
//       Serial.println("44 Hz");
//       break;
//     case MPU6050_BAND_21_HZ:
//       Serial.println("21 Hz");
//       break;
//     case MPU6050_BAND_10_HZ:
//       Serial.println("10 Hz");
//       break;
//     case MPU6050_BAND_5_HZ:
//       Serial.println("5 Hz");
//       break;
//   }
// }

// void Mpu6050::fetchSensorData() {
//   mpu.getEvent(&a, &g, &temp);
// }

// void Mpu6050::printMpu6050Data() {
//   fetchSensorData();

//   // Print accelerometer values
//   Serial.printf("G Force X: %f, Y: %f, Z: %f m/s^2 \n", a.acceleration.x, a.acceleration.y, a.acceleration.z);

//   // Print gyroscope values
//   Serial.printf("Rotation X: %f, Y: %f, Z: %f rad/s \n", g.gyro.x, g.gyro.y, g.gyro.z);

//   // Print temperature
//   Serial.printf("Temperature: %f degC \n\n", temp.temperature);
// }

// // Call fetchSensorData() before calling this function
// sensors_event_t Mpu6050::getMpu6050Data()
// {
//   return a, g, temp;
// }

// // Call fetchSensorData() before calling this function
// sensors_vec_t Mpu6050::getAccelerationData() {
//   return a.acceleration;
// }

// // Call fetchSensorData() before calling this function
// sensors_vec_t Mpu6050::getGyroData() {
//   return g.gyro;
// }

// // Call fetchSensorData() before calling this function
// float Mpu6050::getTempData() {
//   return temp.temperature;
// }