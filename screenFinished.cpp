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
#define LINE(x) (60+x*28)
    
     char buffer[200];
    _tft->fillScreen(ILI9341_WHITE);
    _tft->setTextColor(ILI9341_GREEN,ILI9341_WHITE);
    _tft->setCursor(24, LINE(0));       
    switch(_cause)
    {
        case END_CURRENT_LOW:  _tft->println("LOW CURRENT");break;
        case END_VOLTAGE_LOW:  _tft->println("LOW VOLTAGE");break;
        case END_CURRENT_HIGH: _tft->println("HIGH CURRENT");break;
        default:
            break;
    }
    
    _tft->setCursor(24, LINE(1));    
    int mn=_config->duration;
    int h;
    h=mn/60;
    mn-=h*60;
    sprintf(buffer,"Dur : %d:%d mn",h,mn);
    _tft->println(buffer);

    _tft->setCursor(24, LINE(2));       
    float f=_config->sumMa;
    f/=3600.;
    sprintf(buffer,"Cap : %d mA",(int)f);
    _tft->println(buffer);
}
// EOF