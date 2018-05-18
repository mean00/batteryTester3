/***************************************************
 Battery Tester
 * GPL v2
 * (c) mean 2018 fixounet@free.fr
 ****************************************************/

#include "screenInclude.h"
#include "screenFinished.h"
#include "voltage.h"

/**

*/
finishedScreen::finishedScreen(   batConfig *c,EndOfChargeCause cause) : batScreen(c)
{
    _cause=cause;
}
/**
 */
batScreen *finishedScreen::process(int mV,int mA,int currentTime,int leftRight,bool pressed)
{
    drawVoltageAndCurrent(mV, mA);   
    return NULL;
}
/**
 */
void finishedScreen::draw()
{
     char buffer[200];
    _tft->fillScreen(ILI9341_WHITE);
    _tft->setTextColor(ILI9341_GREEN,ILI9341_WHITE);
    _tft->setCursor(24, 8);       
    _tft->println("DONE");
    
    _tft->setCursor(24, 32);       
    sprintf(buffer,"Duration : %d mn",_config->duration);
    _tft->println(buffer);

    _tft->setCursor(24, 60);       
    float f=_config->sumMa;
    f/=3600.;
    sprintf(buffer,"Capacity : %d mn",(int)f);
    _tft->println(buffer);
}
// EOF