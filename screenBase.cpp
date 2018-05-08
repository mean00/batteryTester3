/***************************************************
 Battery Tester
 * GPL v2
 * (c) mean 2018 fixounet@free.fr
 ****************************************************/

#include <Wire.h>
#include "SPI.h"
#include "Adafruit_GFX_AS.h"
#include "Adafruit_ILI9341_STM.h"
#include "screenBase.h"
#include "backgrounds/background.h"

/**
 */
void batScreen::prettyPrint(int val,int x,int y,const char *unit)
{
     char printBuffer[256];
     char ext[10];
     
     if(val<1000)
     {
         sprintf(printBuffer,"%d m%c",val,unit[0]);
     }else
     {
         float v=val;
         v/=1000.;
         sprintf(printBuffer,"%1.2f %c",v,unit[0]);
     }
     
    _tft->setCursor(x, y);   
    _tft->println(printBuffer);
}

/**
 */
void batScreen::drawBitmap(int width, int height, int wx, int wy, int fgcolor, int bgcolor, const uint8_t *data)
{
    uint8_t *p=(uint8_t *)data;    
    static uint16_t line[320];
    
    width>>=3;
    for(int y=0;y<height;y++)
    {
        uint16_t *o=line;
        _tft-> setAddrWindow(wx, wy+y, wx+width*8, wy+y);
        for(int x=0;x<width;x++)
        {
            int stack=*p++;
            for(int step=0;step<8;step++)
            {
                int color;
                if(stack&0x80)                                        
                    color=fgcolor;
                else
                    color=bgcolor;
                *o++=color;
                stack<<=1;
            }            
        }    
        _tft->pushColors(line,width*8,0);
    }   
}

/**
 */
void batScreen::drawBackground()
{
    drawBitmap(320,240,0,0,0,0xffff,background+11);
}
// EOF