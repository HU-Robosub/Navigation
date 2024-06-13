#include <Arduino.h>
#include <Common.h>
#include <Adafruit_MPU6050.h>
#include <LSM303.h>
#include "pid.h"
#include <Servo.h>

#define OWN_ADDRESS 0x06
#define I2C_SDA0 4
#define I2C_SCL0 5
#define I2C_SDA1 18
#define I2C_SCL1 19

// Values from calibration script DON'T CHANGE
#define GYRO_OFFSET_X 35.62
#define GYRO_OFFSET_Y 0.35
#define GYRO_OFFSET_Z -0.13

// Servo Control
#define PIN_SG90 18

// PID Configuration
#define PWM_PIN 18
#define MIN_PID -30
#define MAX_PID 30
#define MIN_PWM 255
#define MAX_PWM -255

MbedI2C Wire2(I2C_SDA1, I2C_SCL1);
TwoWire *Wire_PTR = &Wire;

float all_data[8];
Adafruit_MPU6050 mpu;
Servo SG90;
LSM303 compass;

// Struct to receive the data from master
struct MotorData
{
  int pwmChannel;
  int dutyCycle;
} motorData;

int pwmChannel = 0;
int dutyCycle = 0;

void receiveEvent(int numBytes)
{
  while (Wire.available() >= 2)
  {
    Wire.readBytes((byte *)&motorData, sizeof(motorData));
    pwmChannel = motorData.pwmChannel;
    dutyCycle = motorData.dutyCycle;
  }
  Serial.println("Received Event");
}

void requestEventMaster()
{
  Serial.println("Received request for sensor data...");
  Serial.println("Sending sensor data...");
  for (int i = 0; i < 8; i++)
  {
    Wire2.write((byte*)&all_data[i], 4);
    Serial.println(all_data[i]);
  }
}

void rotateServo(int startAngle, int endAngle, unsigned long wait)
{
  if (startAngle < endAngle)
  {
    for (int angle = startAngle; angle <= endAngle; angle++)
    {
      SG90.write(angle);
      delay(wait);
    }
  }
  else
  {
    for (int angle = startAngle; angle >= endAngle; angle--)
    {
      SG90.write(angle);
      delay(wait);
    }
  }
  delay(100);
}

int calculateServoPosition(float pidOutput, float pidMin, float pidMax, int servoMin, int servoMax)
{
  pidOutput = constrain(pidOutput, pidMin, pidMax);
  int servoPosition = map(pidOutput, pidMin, pidMax, servoMin, servoMax);
  return servoPosition;
}

void setup()
{
  Serial.begin(9600);
  while (!Serial)
  {}

  Wire.begin();
  Wire2.begin(OWN_ADDRESS);
  Wire2.onRequest(requestEventMaster);
  Wire.onReceive(receiveEvent);

  Serial.println("Adafruit MPU6050 test!");

  while (!mpu.begin(MPU6050_I2CADDR_DEFAULT, Wire_PTR))
  {
    Serial.println("Failed to find MPU6050 chip");
    delay(100);
  }

  Serial.println("MPU6050 Found!");
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  Serial.println("");
  delay(100);

  SG90.attach(PIN_SG90, 400, 2600);

  compass.init();
  compass.enableDefault();
  compass.m_min = (LSM303::vector<int16_t>){ -1212, -265, -863};
  compass.m_max = (LSM303::vector<int16_t>){ -257, 610, -18};

  set_gains(1.0, 0.4, 0.1);
  set_setpoint(33.0);
}

void loop()
{
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  compass.read();

  all_data[0] = a.acceleration.x;
  all_data[1] = a.acceleration.y;
  all_data[2] = a.acceleration.z;
  all_data[3] = g.gyro.x;
  all_data[4] = g.gyro.y;
  all_data[5] = g.gyro.z;
  all_data[6] = temp.temperature;
  all_data[7] = compass.heading();

  Serial.println(a.gyro.pitch);
  set_process_variable(a.gyro.pitch);
  set_setpoint(10);

  float pid = calculate_pid();
  Serial.print("PID: ");
  Serial.println(pid);

  float pidMin = 0.0;
  float pidMax = 50.0;
  int servoMin = 0;
  int servoMax = 180;
  unsigned long wait = 15;

  int targetPosition = calculateServoPosition(pid, pidMin, pidMax, servoMin, servoMax);
  int currentPosition = SG90.read();

  rotateServo(currentPosition, targetPosition, wait);

  delay(500);
}