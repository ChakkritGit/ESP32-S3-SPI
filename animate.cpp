#include "animate.h"
#include "display.h"

// Global variables and constants
AnimatedGIF gif;
GIFContext gifContext = {&lcd, nullptr, 0, 0}; // ใช้ lcd แทน oled

// Assume maximum canvas size for all GIFs
const size_t maxCanvasWidth = GIF_WIDTH;
const size_t maxCanvasHeight = GIF_HEIGHT;
const size_t frameBufferSize = maxCanvasWidth * maxCanvasHeight * 2; // 2 bytes per pixel (RGB565)

GIFData gifFiles[] = {
    {(uint8_t *)SIGH_EMOTE, sizeof(SIGH_EMOTE)},
    // Add other GIFs here (up to 15)
};

void printMemoryStats()
{
  Serial.printf("Free heap: %u bytes\n", heap_caps_get_free_size(MALLOC_CAP_DEFAULT));
  Serial.printf("Free PSRAM: %u bytes\n", heap_caps_get_free_size(MALLOC_CAP_SPIRAM));
}

void initializeGIF()
{
  gif.begin(GIF_PALETTE_RGB565_BE);

  // Allocate shared frame buffer in PSRAM (only once during initialization)
  if (gifContext.sharedFrameBuffer == nullptr)
  {
    gifContext.sharedFrameBuffer = (uint8_t *)heap_caps_malloc(frameBufferSize, MALLOC_CAP_8BIT);
    if (!gifContext.sharedFrameBuffer)
    {
      Serial.println("Error: Failed to allocate shared frame buffer in PSRAM.");
    }
  }
  printMemoryStats();
}

void cleanupGIFContext()
{
  if (gifContext.sharedFrameBuffer)
  {
    heap_caps_free(gifContext.sharedFrameBuffer);
    gifContext.sharedFrameBuffer = nullptr;
  }
  gif.close();
}

void GIFDraw(GIFDRAW *pDraw)
{
  if (pDraw->y == 0)
  {
    gifContext.lcd->setAddrWindow(gifContext.offsetX + pDraw->iX, gifContext.offsetY + pDraw->iY, pDraw->iWidth, pDraw->iHeight);
  }
  gifContext.lcd->pushPixels((uint16_t *)pDraw->pPixels, pDraw->iWidth, DRAW_TO_LCD | DRAW_WITH_DMA);
}

void playGIF(uint8_t *gifData, size_t gifSize, bool loop = false)
{
  if (!gif.open(gifData, gifSize, GIFDraw))
  {
    Serial.println("Error: Failed to open GIF file.");
    cleanupGIFContext();
    return;
  }

  gifContext.offsetX = (lcd.width() - gif.getCanvasWidth()) / 2;
  gifContext.offsetY = (lcd.height() - gif.getCanvasHeight()) / 2;
  size_t currentFrameBufferSize = gif.getCanvasWidth() * (gif.getCanvasHeight() + 2);

  if (gifContext.sharedFrameBuffer == nullptr || currentFrameBufferSize != frameBufferSize)
  {
    gifContext.sharedFrameBuffer = (uint8_t *)heap_caps_malloc(currentFrameBufferSize, MALLOC_CAP_8BIT);
    if (!gifContext.sharedFrameBuffer)
    {
      Serial.printf("Memory Error: Failed to allocate %zu bytes\n", currentFrameBufferSize);
      cleanupGIFContext();
      return;
    }
  }

  gif.setDrawType(GIF_DRAW_COOKED);
  gif.setFrameBuf(gifContext.sharedFrameBuffer);

  const int targetFPS = GIF_FPS;
  const int frameDelay = 1000000 / targetFPS;
  unsigned long previousTime = 0;
  unsigned long currentTime = 0;

  do
  {
    while (gif.playFrame(false, nullptr))
    {
      currentTime = micros();
      if (currentTime - previousTime >= frameDelay)
      {
        previousTime = currentTime;
      }
      else
      {
        delayMicroseconds(frameDelay - (currentTime - previousTime));
        previousTime = micros();
      }
    }

    if (loop)
    {
      gif.reset();
    }
  } while (loop);

  cleanupGIFContext();
}

// Function to play a random GIF
void playRandomGIF()
{
  while (true)
  {
    int randomIndex = random(0, TOTAL_GIFS);

    uint8_t *gifData = gifFiles[randomIndex].data;
    size_t gifSize = gifFiles[randomIndex].size;

    playGIF(gifData, gifSize, false);

    unsigned long delayTime = random(2000, 4000);
    unsigned long startDelayTime = millis();

    playGIF((uint8_t *)REST_EMOTE, sizeof(REST_EMOTE), false);

    while (millis() - startDelayTime < delayTime)
    {
    }
  }
}
