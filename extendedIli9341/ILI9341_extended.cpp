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
    c -= gfxFont->first;
    GFXglyph *glyph  = gfxFont->glyph+c;
    x+= glyph->xOffset;
    y+= glyph->yOffset;    
    
    uint8_t *p= gfxFont->bitmap+glyph->bitmapOffset;
    int    finalColor;    
    
    int  w  = glyph->width;
    int  h  = glyph->height;
    uint16_t *column=(uint16_t *)alloca(w*2);
    uint16_t *col;
    int  bits = 0, bit = 0;
    
    for(int yy=0; yy<h; yy++) 
    {
        setAddrWindow(x,y+yy,x+w, y+yy+1);
        col=column;
        for(int xx=0; xx<w; xx++) 
        {
            if(!bit)
            {
                bits= *p++;
                bit = 0x80;
            }            
            if(bits & bit) 
                finalColor=color;  
            else
                finalColor=bg;
            *(col++)=finalColor;            
            bit=bit>>1;
        }
        pushColors(column,w,0);
    }
    return glyph->xAdvance;
}
/**
 * 
 * @param st
 */
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