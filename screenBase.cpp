/***************************************************
 Battery Tester
 * GPL v2
 * (c) mean 2018 fixounet@free.fr
 ****************************************************/

#include "screenInclude.h"
#include "backgrounds/background_compressed.h"
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
   
    _tft->drawRLEBitmap(width,height,wx,wy,fgcolor,bgcolor,data);
}

/**
 */
void batScreen::drawBackground()
{
    drawBitmap(320,240,0,0,0xffff,0,background);
}
/**
 */
void batScreen::drawVoltageAndCurrent(int mV, int mA)
{
    prettyPrint(mV,40,240-9-28,"V");
    prettyPrint(mA,160+43,240-9-28,"A");
}


void batScreen::disableCurrent()
{
    _config->mcp->setVoltage(0,false);
}


// EOF