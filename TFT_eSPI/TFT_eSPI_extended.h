
#pragma once
#include "MapleFreeRTOS1000_pp.h"
#include "TFT_eSPI.h"

extern int tftLocked;

class  TFT_eSPI_extended : public TFT_eSPI
{
public:    
   typedef enum FontSize
   {
    SmallFont,MediumFont,BigFont
   };
   class FontInfo
    {
    public:
      int               maxHeight;          
      int               maxWidth;
      uint16_t         *filler;
      const GFXfont    *font;        
    };

    
    TFT_eSPI_extended(xMutex *tex,int16_t _W = TFT_WIDTH, int16_t _H = TFT_HEIGHT) : TFT_eSPI(_W,_H)
    {
        this->tex=tex;
        currentFont=NULL;
    }
    void drawBitmap(int width, int height, int wx, int wy, int fgcolor, int bgcolor, const uint8_t *data);
    void drawRLEBitmap(int width, int height, int wx, int wy, int fgcolor, int bgcolor, const uint8_t *data);
    void  setFontFamily(const GFXfont *small, const GFXfont *medium, const GFXfont *big);        
    void  setFontSize(FontSize size);


    
protected:    
    xMutex *tex;
    void spiLock() {tex->lock();tftLocked++;}
    void spiUnlock() {tftLocked--;if(tftLocked<0) xAssert(0);tex->unlock();}
    int myDrawChar(int x, int y, unsigned char c,  int color, int bg,FontInfo &infos);
    void  myDrawString(const char *st, int padd_up_to_n_pixels=0);
    int mySquare(int x, int y, int w, int xheight, uint16_t *filler);
    
    FontInfo          fontInfo[3];
    FontInfo          *currentFont;    
};

// eof
