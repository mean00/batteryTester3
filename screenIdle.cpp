#include <Wire.h>
#include "SPI.h"
#include "Adafruit_GFX_AS.h"
#include "Adafruit_ILI9341_STM.h"
#include "screenIdle.h"
#include "backgrounds/background.h"
/**

*/
idleScreen::idleScreen(   batConfig *c,Adafruit_ILI9341_STM *tft) : batScreen(c,tft)
{
    _tft->setCursor(10, 50);   
    _tft->println("Volt");

    _tft->setCursor(10, 80);   
    _tft->println("Amp");

}
/**
 */
batScreen *idleScreen::process(int mV,int mA,int currentTime,int leftRight,bool pressed)
{
    prettyPrint(mV,120,50,"V");
    prettyPrint(mA,120,80,"A");
    return NULL;
}
/**
 */
void idleScreen::draw()
{
  
    
}
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

void batScreen::drawBitmap(int width, int height, int wx, int wy, int fgcolor, int bgcolor, const uint8_t *data)
{
    uint8_t *p=(uint8_t *)data;
    
    
    for(int y=0;y<height;y++)
    {
        for(int x=0;x<width>>3;x++)
        {
            int stack=*p++;
            for(int step=0;step<8;step++)
            {
                int color=bgcolor;
                if(stack&0x80)
                    color=fgcolor;
                _tft->  drawPixel(wx+x*8+step,wy+y,color);                
                stack<<=1;
            }
        }        
    }   
}
//--
void batScreen::drawBackground()
{
    drawBitmap(320,240,0,0,0,0xffff,background+11);
}