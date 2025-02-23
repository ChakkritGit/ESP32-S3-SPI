#include <Wire.h>
#include <MPU6050.h>
#include "gyroscope.h"

MPU6050 mpu;

// Threshold for shake detection
const int shakeThreshold = 10000;
int16_t ax, ay, az;
int16_t gx, gy, gz;

void initializeMPU6050() {
  Wire.begin(MPU6050_SDA, MPU6050_SCL);  // กำหนดขา SDA, SCL
  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed.");
    while (1)
      ;
  }
  Serial.println("MPU6050 initialized!");
}

bool detectShake() {
  mpu.getAcceleration(&ax, &ay, &az);
  mpu.getRotation(&gx, &gy, &gz);

  // Detect shake if any axis exceeds the threshold
  if (abs(ax) > shakeThreshold || abs(ay) > shakeThreshold || abs(az) > shakeThreshold) {
    return true;
  }
  return false;
}
