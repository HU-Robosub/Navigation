#include "Common.h"
#include "Mpu6050.h"
#include <LSM303.h>

#define SDA2 33
#define SCL2 32
#define SLAVE_ADDRESS 0x04 // TODO AUTOMATIC UPDATING

Mpu6050 mpu;
LSM303 compass;

// TwoWire SensorBus = TwoWire(0);
// TwoWire MainBus = TwoWire(1);

int reg;

void receiveEventMaster(int numBytes) {
  while (Wire1.available()) {
    reg = Wire1.read();
    Serial.println(reg);
  }
}

void requestEventMaster() {
  Serial.println("Recieved a request!");
  mpu.fetchSensorData();

  switch(reg)
  {
    // Accelerometer
    case 0:
    {
      sensors_vec_t accel_data = mpu.getAccelerationData();
      Wire1.write((byte *)&accel_data, sizeof(sensors_vec_t));
      Serial.printf("Accelerometer: %f %f %f \n", accel_data.x, accel_data.y, accel_data.z);
      break;
    }
    // Gyroscope
    case 1:
    {
      sensors_vec_t gyro_data = mpu.getGyroData();
      Wire1.write((byte *)&gyro_data, sizeof(sensors_vec_t));
      Serial.printf("Gyroscope: %f %f %f \n", gyro_data.x, gyro_data.y, gyro_data.z);
      break;
    }
    // Temperature
    case 2:
    {
      float temp_data = mpu.getTempData();
      Wire1.write((byte *)&temp_data, sizeof(float));
      Serial.printf("Temperature: %f \n", temp_data);
      break;
    }
    // Compass heading
    case 3:
    {
      compass.read();
      int compassHeading = compass.heading();
      Wire1.write(compassHeading);
      break;
    }
  }
}

void setup()
{
  Serial.begin(9600);
  while(!Serial)
  {
    delay(1000); // Wait until serial console opens
  }
  // Setup busses
  Wire.setPins(SDA, SCL);
  Wire.begin();

  Wire1.setPins(SDA2, SCL2);
  Wire1.begin(SLAVE_ADDRESS);
  Wire1.onReceive(receiveEventMaster);
  Wire1.onRequest(requestEventMaster);

  // Initialize MPU6050
  if (!mpu.begin())
  {
    Serial.println("Failed to find MPU6050 chip");
    while(1)
    {
      delay(10);
    }
  }
  Serial.println("MPU6050 found!");
  
  // Setup MPU6050
  mpu.setupMPU6050();

  // Setup LSM303
  compass.init();
  compass.enableDefault();

  compass.m_min = (LSM303::vector<int16_t>){ -1212,   -265,   -863};
  compass.m_max = (LSM303::vector<int16_t>){  -257,   +610,    -18};
}

void loop()
{
  // Print compass heading
  // compass.read();
  // float heading = compass.heading();
  // Serial.print("Compass Heading: ");
  // Serial.println(heading);

  // // Print MPU6050 data
  // mpu.printMPU6050Data();

  // Delay printing
  // delay(2000);
}