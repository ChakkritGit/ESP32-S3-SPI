#include "display.h"

BB_SPI_LCD lcd;

void initializeLCD()
{
  Serial.println("Initializing ST7789 display...");

  // Initialize ST7789 display
  if (!lcd.begin(LCD_ST7789, FLAGS_NONE, SPI_FREQUENCY, CS_PIN, DC_PIN, RST_PIN,
                 -1, -1, MOSI_PIN, CLK_PIN))
  {
    Serial.println("Error: ST7789 initialization failed.");
    return;
  }

  lcd.setRotation(LCD_ORIENTATION_90); // หมุนจอ 90 องศา
  lcd.allocBuffer();                   // จองบัฟเฟอร์สำหรับการวาดกราฟิก
  lcd.fillScreen(TFT_BLACK);           // เคลียร์หน้าจอเป็นสีดำ
  lcd.setFont(FONT_8x8);               // ตั้งค่าฟอนต์
  lcd.setTextColor(TFT_WHITE);         // ตั้งค่าสีตัวอักษร
}

void displayBootMessage(const char *message)
{
  int16_t x1, y1;
  uint16_t textWidth, textHeight;

  lcd.getTextBounds(message, 0, 0, &x1, &y1, &textWidth, &textHeight);

  int16_t centeredX = (DISPLAY_WIDTH - textWidth) / 2;
  int16_t centeredY = (DISPLAY_HEIGHT - textHeight) / 2;

  lcd.setCursor(centeredX, centeredY);
  lcd.println(message);
}
