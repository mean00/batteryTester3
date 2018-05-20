#include "ILI9341_extended.h"
/**
 * 
 * @param _CS
 * @param _DC
 * @param _RST
 */
ILI9341::ILI9341(int8_t _CS, int8_t _DC, int8_t _RST) :Adafruit_ILI9341_STM( _CS,  _DC,  _RST) 
{
    gfxFont=NULL;
}
/**
 * 
 */
ILI9341::~ILI9341()
{
    
}
void ILI9341::setFont (const GFXfont *f)
{
    gfxFont=f;
}
#define pgm_read_dword(addr) (*(const unsigned long *)(addr))
#define pgm_read_byte(addr) (*(const unsigned char *)(addr))
#define pgm_read_pointer(addr) ((void *)pgm_read_dword(addr))
/**
 * 
 * @param x
 * @param y
 * @param c
 * @param color
 * @param bg
 * @return 
 */
int ILI9341::myDrawChar(int x, int y, unsigned char c,  int color, int bg)
{
    c -= (uint8_t)pgm_read_byte(&gfxFont->first);
    GFXglyph *glyph  = &(((GFXglyph *)pgm_read_pointer(&gfxFont->glyph))[c]);
    uint8_t  *bitmap = gfxFont->bitmap;
    int  bo = glyph->bitmapOffset;
    int  w  = glyph->width;
    int  h  = glyph->height;
    int  xo = glyph->xOffset;
    int  yo = glyph->yOffset;
    int  bits = 0, bit = 0;

    uint8_t *p=bitmap+bo;
    int    finalColor;
    //  startWrite();
    for(int yy=0; yy<h; yy++) 
    {
        for(int xx=0; xx<w; xx++) 
        {
            if(!bit)
            {
                bits = *p;p++;
                bit=0x80;
            }            
            if(bits & bit) 
                finalColor=color;  
            else
                finalColor=bg;
            writePixel(x+xo+xx, y+yo+yy, finalColor);                
            bit=bit>>1;
        }
    }
    //    endWrite();
    
    return glyph->xAdvance;
}
 void  ILI9341::myDrawString(const char *st)
 {
     if(!gfxFont)
         return;
     int l=strlen(st);
     for(int i=0;i<l;i++)
     {
         int of=myDrawChar(cursor_x,cursor_y,st[i],textcolor,textbgcolor);
         cursor_x+=of;
         if(cursor_x>=_width) return;
     }
 }

// EOF