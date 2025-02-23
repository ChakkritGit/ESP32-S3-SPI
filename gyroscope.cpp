#include <Wire.h>
#include <MPU6050.h>
#include "gyroscope.h"

MPU6050 mpu;

// Threshold for shake detection
const int shakeThreshold = 3000; // ปรับค่า threshold ให้เหมาะสม
int16_t ax, ay, az;
int16_t gx, gy, gz;

void initializeMPU6050() {
  Wire.begin(MPU6050_SDA, MPU6050_SCL);  // กำหนดขา SDA, SCL
  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed.");
    while (1);
  }
  Serial.println("MPU6050 initialized!");

  // Calibrate MPU6050
  mpu.setXAccelOffset(-100);
  mpu.setYAccelOffset(-100);
  mpu.setZAccelOffset(1000);
  mpu.setXGyroOffset(50);
  mpu.setYGyroOffset(-50);
  mpu.setZGyroOffset(50);
}

bool detectShake() {
  mpu.getAcceleration(&ax, &ay, &az);
  mpu.getRotation(&gx, &gy, &gz);

  // ใช้ low-pass filter เพื่อลด noise
  static int16_t lastAx = 0, lastAy = 0, lastAz = 0;
  ax = (ax + lastAx) / 2;
  ay = (ay + lastAy) / 2;
  az = (az + lastAz) / 2;
  lastAx = ax;
  lastAy = ay;
  lastAz = az;

  // Detect shake if any axis exceeds the threshold
  return (abs(ax) > shakeThreshold || abs(ay) > shakeThreshold || abs(az) > shakeThreshold);
}