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
    
    uint8_t *p= gfxFont->bitmap+glyph->bitmapOffset;
    int    finalColor;    
    
    int  w  = glyph->width;
    int  h  = glyph->height;

    uint16_t *column=(uint16_t *)alloca(w*2*2);
    uint16_t *tail=column+w*2;
    uint16_t *col=column;
    int  bits = 0, bit = 0;
    
    x+= glyph->xOffset;
    y+= glyph->yOffset;    
    
    setAddrWindow(x,y,                  x+w-1, y+h+1);
    for(int i=w*h-1;i>0;i--)
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
        
        if(col>=tail)
        {
            pushColors(column,w*2,0);
            col=column;
        }
    }
    int leftOver=(uint32_t )col-(uint32_t)column;
    pushColors(column,leftOver/2,0);
    return glyph->xAdvance;
}
/**
 * 
 * @param st
 */
 void  ILI9341::myDrawString(const char *st,bool clearBackground)
 {
     if(!gfxFont)
         return;
     int l=strlen(st);
     int w,h;
     getBounding(st,w,h);
     if(clearBackground)
     {        
        fillRect(cursor_x,cursor_y, w, h, textbgcolor);
     }
     for(int i=0;i<l;i++)
     {
         int of=myDrawChar(cursor_x,cursor_y+h,st[i],textcolor,textbgcolor);
         cursor_x+=of;
         if(cursor_x>=_width) return;
     }
 }
/**
 * 
 * @param st
 * @param w
 * @param h
 */
void  ILI9341::getBounding(const char *st, int &w, int &h)
{
     w=0;h=0;
     int l=strlen(st);
     for(int i=0;i<l;i++)
     {
            int c=st[i];
            c -= gfxFont->first;
            GFXglyph *glyph  = gfxFont->glyph+c;
            w+=glyph->xAdvance;       
            if(glyph->height>h)
                h=glyph->height;
     }
}
/**
 * 
 * @param size
 */
void  ILI9341::setFontSize(FontSize size)
{
    switch(size)
    {
        case SmallFont :  gfxFont=gfxFonts[0];break;
        default:
        case MediumFont :  gfxFont=gfxFonts[1];break;
        case BigFont :  gfxFont=gfxFonts[2];break;
    }    
}
/**
 * 
 * @param small
 * @param medium
 * @param big
 */
void  ILI9341::setFontFamily(const GFXfont *small, const GFXfont *medium, const GFXfont *big)
{
    gfxFonts[0]=small;
    gfxFonts[1]=medium;
    gfxFonts[2]=big;
}
// EOF