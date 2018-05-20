
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
                
};