#ifndef ANIMATE_H
#define ANIMATE_H

#include <AnimatedGIF.h>
#include "display.h"
#include "emojis.h"

// Global objects
extern AnimatedGIF gif;

struct GIFContext
{
  BB_SPI_LCD *lcd; // เปลี่ยนจาก oled เป็น lcd เพื่อรองรับ ST7789
  uint8_t *sharedFrameBuffer;
  int offsetX;
  int offsetY;
};

struct GIFData
{
  uint8_t *data; // Pointer to the GIF data
  size_t size;   // Size of the GIF data
};

// Declare the array (no definition here, just a declaration)
extern GIFData gifFiles[];

// GIF SETTINGS
#define GIF_FPS 15
#define GIF_HEIGHT 128
#define GIF_WIDTH 128
// Define the macro to count the number of GIFs in the array
#define TOTAL_GIFS (sizeof(gifFiles) / sizeof(gifFiles[0]))
#define REST_EMOTE rest
#define SIGH_EMOTE sigh
#define SHAKE_EMOTE shake

// Function declarations
void cleanupGIFContext(void);
void GIFDraw(GIFDRAW *pDraw);
void playGIF(uint8_t *gifData, size_t gifSize, bool loop);
void playRandomGIF(void);
void initializeGIF(void);
void printMemoryStats(void);
void playShakeGIF(void);

#endif
