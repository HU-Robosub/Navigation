#include <Common.h>
#include <Adafruit_MPU6050.h>
#include <LSM303.h>

#define OWN_ADDRESS 0x06
// GPIO pins of raspberry pico
#define I2C_SDA0 4
#define I2C_SCL0 5
#define I2C_SDA1 18
#define I2C_SCL1 19

MbedI2C Wire2(I2C_SDA1, I2C_SCL1);

TwoWire *Wire_PTR = &Wire;

float all_data[7];

Adafruit_MPU6050 mpu;
LSM303 compass;

void requestEventMaster() {  
  // Send Sensor data
  Serial.println("Recieved request for sensor data...");
  Serial.println("Sending sensor data...");
  for (int i=0; i < 8; i++) {
    Wire2.write((byte*)&all_data[i], 4);
    
  }
}

void setup(void) {
  Serial.begin(9600);
  while (!Serial) {
    delay(1000); // will pause until serial console opens
  }
  // Setup busses
  // initialize I2C bus for sensor bus
  Wire.begin();  

  // initialize I2C bus for master connection
  Wire2.begin(OWN_ADDRESS);
  Wire2.onRequest(requestEventMaster);

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  while (!mpu.begin(MPU6050_I2CADDR_DEFAULT, Wire_PTR)) {
    Serial.println("Failed to find MPU6050 chip");
    delay(100);
  }

  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_2_G); // Possible values 2, 4, 8, 16
  mpu.setGyroRange(MPU6050_RANGE_500_DEG); // Possible values 250, 500, 1000, 2000
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ); // Possible values 260, 184, 94, 44, 21, 10, 5

  Serial.println("");
  delay(100);

  // Setup LSM303
  compass.init();
  compass.enableDefault();

  compass.m_min = (LSM303::vector<int16_t>){ -1212,   -265,   -863};
  compass.m_max = (LSM303::vector<int16_t>){  -257,   +610,    -18};
}

void loop() {
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  compass.read();

  all_data[0]= a.acceleration.x;
  all_data[1]= a.acceleration.y;
  all_data[2]= a.acceleration.z;
  
  all_data[3]= g.gyro.x;
  all_data[4]= g.gyro.y;
  all_data[5]= g.gyro.z;
  
  all_data[6]= temp.temperature;
  all_data[7]= compass.heading();
  
  // Print loop all data
  for (int i=0; i < 7; i++) {
    Serial.print(all_data[i]);
    Serial.print(", ");
    Serial.println();
  }

  delay(500);
}