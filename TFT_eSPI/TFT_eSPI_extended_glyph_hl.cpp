/**
 *  \brief Extended ILI9341 driver with
 *    * Support for adafruit "truetype" fonts
 *    * Mono bitmap draw (compressed or not)
 * 
 * @param _CS
 * @param _DC
 * @param _RST
 */
#include "TFT_eSPI_extended.h"

#define pgm_read_dword(addr) (*(const unsigned long *)(addr))
#define pgm_read_byte(addr) (*(const unsigned char *)(addr))
#define pgm_read_pointer(addr) ((void *)pgm_read_dword(addr))

/**
 * 
 * @param st
 */
 void  TFT_eSPI_extended::myDrawString(const char *st,int padd_up_to_n_pixels)
 {
     if(!currentFont)
         return;
     int l=strlen(st);
   
     int lastColumn=0;
     
     int endX=cursor_x+padd_up_to_n_pixels;
     
     for(int i=0;i<l;i++)
     {
         int of=myDrawChar(cursor_x,cursor_y+currentFont->maxHeight,
                           st[i],
                           textcolor,textbgcolor,*currentFont);
         cursor_x+=of;
         if(cursor_x>=_width) return;
     }
     int leftOver=endX-cursor_x;
     if(leftOver>0)
     {
         for(int i=0;i<2*currentFont->maxWidth;i++)
             currentFont->filler[i]=textbgcolor;
         while(leftOver>0)
         {
             int rnd=leftOver;
            if(rnd>currentFont->maxWidth) rnd=currentFont->maxWidth;
            mySquare(cursor_x,cursor_y,
                  rnd, currentFont->maxHeight+2,
                  currentFont->filler);
            cursor_x+=rnd;
            leftOver=endX-cursor_x;
            
         }
     }
 }

/**
 * 
 * @param size
 */
void  TFT_eSPI_extended::setFontSize(FontSize size)
{
    switch(size)
    {
        case SmallFont :  currentFont=fontInfo+0;break;
        case BigFont :   currentFont=fontInfo+2;break;
        default:
        case MediumFont :   currentFont=fontInfo+1;break;
        
    }    
}
/**
 * \fn checkFont
 * \brief extract max width/ max height from the font
 */
static void checkFont(const GFXfont *font, TFT_eSPI_extended::FontInfo *info)
{
    int mW=0,mH=0;
    int x,y;
   for(int i=font->first;i<font->last;i++)
   {
         GFXglyph *glyph  = font->glyph+i-font->first;
         x=glyph->xAdvance;
         y=-glyph->yOffset;
         if(x>mW) mW=x;         
         if(y>mH) mH=y;
   }
    info->maxHeight=mH + 1;
    info->maxWidth=mW;
    info->filler=new uint16_t[mW*2+1];
    info->font=font;
}

/**
 * 
 * @param small
 * @param medium
 * @param big
 */
void  TFT_eSPI_extended::setFontFamily(const GFXfont *small, const GFXfont *medium, const GFXfont *big)
{
    checkFont(small, fontInfo+0);
    checkFont(medium,fontInfo+1);
    checkFont(big,   fontInfo+2);
}



// EOF