
#pragma once

#include "Adafruit_GFX_AS.h" //
#include "Adafruit_ILI9341_STM.h" //
#include "gfxfont.h"
/**
 */
class ILI9341 : public Adafruit_ILI9341_STM
{
public:  
  typedef enum FontSize
  {
    SmallFont,MediumFont,BigFont
  };
  
        ILI9341(int8_t _CS, int8_t _DC, int8_t _RST = -1);
        ~ILI9341();
        
        //--
        void  setFont(const GFXfont *f);   
        void  setFontFamily(const GFXfont *small, const GFXfont *medium, const GFXfont *big);
        void  myDrawString(const char *st, bool clearBackground=true);
        void  getBounding(const char *st, int &w, int &h);
        void  setFontSize(FontSize size);
protected:
        int   myDrawChar(int x, int y, unsigned char c,  int color, int bg);

        const GFXfont    *gfxFont;
        const GFXfont    *gfxFonts[3];

};
