#ifndef DISPLAY_H
#define DISPLAY_H

#include <bb_spi_lcd.h>

// Global objects
extern BB_SPI_LCD lcd; // เปลี่ยนจาก oled เป็น lcd เพื่อให้ตรงกับ ST7789

// ST7789 PINOUT for Xiao ESP32-C3
// GND | GND (0V)
// VCC | 3.3V (Xiao ESP32-C3 ใช้ 3.3V เท่านั้น ห้ามใช้ 5V)
// DIN | MOSI (6)
// SCK | SCLK (7)
// DC  | Data/Command (3)
// RST | Reset (2)
// CS  | Chip Select (10)
// BL  | Backlight (4) - ถ้ามี

// Pin configuration for Display
#define MISO_PIN -1    // ไม่ได้ใช้
#define MOSI_PIN 37    // GPIO37 (สาย SDA/MOSI)
#define CLK_PIN 36     // GPIO36 (สาย SCL/CLK)
#define CS_PIN 35      // GPIO35 (สาย CS)
#define DC_PIN 33      // GPIO33 (สาย DC)
#define RST_PIN 34     // GPIO34 (สาย RST)
#define BL_PIN 21      // GPIO21 (สาย BL - Backlight)

// SPI Frequency (สูงสุด 40MHz แต่ 20MHz เสถียรกว่า)
#define SPI_FREQUENCY 20000000

// Display dimensions
#define DISPLAY_WIDTH 128 // หรือ 240 ถ้าเป็นจอ 240x240
#define DISPLAY_HEIGHT 128
#define DISPLAY_BRIGHTNESS 255 // ค่าระดับความสว่าง 0-255

void initializeLCD();
void displayBootMessage(const char *message);

#endif
