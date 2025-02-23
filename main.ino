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
  // No need to initialize the RGB LED
  delay(2000);
  initializeGIF();
}

// the loop function runs over and over again forever
void loop() {
  static bool isShaking = false;

  // Check if shake is detected
  if (detectShake()) {
    if (!isShaking) {
      playShakeGIF();
      isShaking = true;
      delay(500); // Small delay to prevent continuous trigger
    }
  } else {
    // If no shake, play random GIF periodically
    static unsigned long lastPlayTime = 0;
    unsigned long currentMillis = millis();
    if (currentMillis - lastPlayTime > 5000) { // Every 5 seconds
      playRandomGIF();
      lastPlayTime = currentMillis;
    }
    isShaking = false;
  }

  delay(100);
}