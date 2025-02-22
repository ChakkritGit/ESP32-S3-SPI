#include <Arduino.h>
#include "display.h"
#include "animate.h"

void setup() {
  Serial.begin(115200);
  Serial.println("Hello World!");
  initializeLCD();
  displayBootMessage("Hello World!");
  // No need to initialize the RGB LED
  delay(2000);
  initializeGIF();
}

// the loop function runs over and over again forever
void loop() {
  Serial.println("Testing from c3");
  // playGIF((uint8_t*)REST_EMOTE, sizeof(REST_EMOTE), true);
  playRandomGIF();
}
