/***************************************************
 Battery Tester
 * GPL v2
 * (c) mean 2018 fixounet@free.fr
 ****************************************************/

#include "screenInclude.h"
#include "backgrounds/background.h"
#include "Adafruit_MCP4725.h"

/**
 */
void myPrettyPrint(ILI9341 *_tft,int val,int x,int y,const char *unit)
{
     char printBuffer[256];
     char ext[10];
     
     if(val<1000)
     {
         sprintf(printBuffer,"%3d m%c",val,unit[0]);
     }else
     {
         float v=val;
         v/=1000.;
         sprintf(printBuffer,"%1.2f %c",v,unit[0]);
     }
     
    _tft->setCursor(x, y);   
    _tft->myDrawString(printBuffer);
}
/**
 */
void batScreen::prettyPrint(int val,int x,int y,const char *unit)
{
    ::myPrettyPrint(_tft,val,x,y,unit);
}

/**
 */
void batScreen::drawBitmap(int width, int height, int wx, int wy, int fgcolor, int bgcolor, const uint8_t *data)
{
    uint8_t *p=(uint8_t *)data;    
    uint16_t line[320];
    
    width>>=3;
    for(int y=0;y<height;y++)
    {
        uint16_t *o=line;
        _tft-> setAddrWindow(wx, wy+y, wx+width*8-1, wy+y-1);
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
/**
 */
void batScreen::drawVoltageAndCurrent(int mV, int mA)
{
    prettyPrint(mV,40,240-9,"V");
    prettyPrint(mA,160+43,240-9,"A");
}


void batScreen::disableCurrent()
{
    _config->mcp->setVoltage(0,false);
}


// EOF