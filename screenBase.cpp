/***************************************************
 Battery Tester
 * GPL v2
 * (c) mean 2018 fixounet@free.fr
 ****************************************************/

#include "screenInclude.h"
#include "background_decl.h"
#include "simplerMCP4725.h"

/**
 * 
 * @param _tft
 * @param val
 * @param x
 * @param y
 * @param unit
 */
void myPrettyPrint(TFT_eSPI_extended *_tft,int val,int x,int y,const char *unit)
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
 * \fn myBoundPrettyPrint
 * @param _tft
 * @param val
 * @param x
 * @param y
 * @param unit
 * @param maxWidth
 */
void myBoundPrettyPrint(TFT_eSPI_extended *_tft,int val,int x,int y,const char *unit, int maxWidth)
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
    _tft->myDrawString(printBuffer,maxWidth);
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
    drawBitmap(background_width,background_height,0,0,0xffff,0,background);
}
/**
 */
void batScreen::drawVoltageAndCurrent(const CurrentState &s)
{
    prettyPrint(s.mVoltage,40,240-9-28,"V");
    prettyPrint(s.mCurrent,160+43,240-9-28,"A");
}


void batScreen::disableCurrent()
{
    _config->mcp->setVoltage(0);
}
/**
 */
void batScreen::setTitle(int color, int bgColor,int x, const char *title)
{
    _tft->setTextColor(color,bgColor);  
    _tft->setCursor(x, 0);   
    _tft->myDrawString(title);        
}

// EOF
