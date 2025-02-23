#include <Arduino.h>
#include "display.h"
#include "animate.h"
#include "gyroscope.h"

void setup() {
  Serial.begin(115200);
  Serial.println("Hello World!");
  initializeMPU6050();
  initializeLCD();
  displayBootMessage("Hello World!");
  delay(2000);
  initializeGIF();
}

// the loop function runs over and over again forever
void loop() {
  static bool isShaking = false;
  static unsigned long lastShakeTime = 0;
  static unsigned long lastPlayTime = 0;

  unsigned long currentMillis = millis();

  // ใช้ Low-Pass Filter ลด Noise
  if (detectShake()) {
    if (!isShaking || (currentMillis - lastShakeTime > 300)) { // Debounce 300ms
      playShakeGIF();
      isShaking = true;
      lastShakeTime = currentMillis;
    }
  } else {
    isShaking = false;
    
    // เปลี่ยน GIF ทุก 5 วินาทีถ้าไม่มีการสั่น
    if (currentMillis - lastPlayTime > 5000) {
      playRandomGIF();
      lastPlayTime = currentMillis;
    }
  }

  delay(50); // ลดดีเลย์เพื่อให้ระบบตอบสนองไวขึ้น
}
