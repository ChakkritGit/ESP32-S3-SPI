#ifndef MPU6050_HANDLER_H
#define MPU6050_HANDLER_H

#include <MPU6050.h>

// Pin configuration for MPU6050
#define MPU6050_SDA 15    // GPIO15 (SDA)
#define MPU6050_SCL 16    // GPIO16 (SCL)

// Initialize MPU6050
void initializeMPU6050();

// Detect shake event
bool detectShake();

#endif
