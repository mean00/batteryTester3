
#pragma once

#include "Adafruit_GFX_AS.h"
#include "Adafruit_ILI9341_STM.h"
/**
 */
class ILI9314 : public Adafruit_ILI9341_STM
{
  public:
        ILI9314(int8_t _CS, int8_t _DC, int8_t _RST = -1);
        ~ILI9314();
    
        size_t write(uint8_t c);
        // Draw a character
        void myDrawChar(int16_t x, int16_t y, unsigned char c,  uint16_t color, uint16_t bg, uint8_t size) ;
        
};