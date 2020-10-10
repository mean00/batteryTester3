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
batScreen *finishedScreen::process(const CurrentState &s)
{
    drawVoltageAndCurrent(s);   
    return NULL;
}
/**
 */
void finishedScreen::draw()
{
#define LINE(x) (60+x*28)
     char buffer[200];
     
    int color=ILI9341_GREEN;
    const char *s="??";
    switch(_cause)
    {
        case END_CURRENT_LOW:  s="LOW CURRENT";break;
        case END_VOLTAGE_LOW:  s="LOW VOLTAGE";break;
        case END_CURRENT_HIGH: s="HIGH CURRENT";color=ILI9341_RED;break;
        default:
            break;
    }
    
    _tft->fillScreen(color);
      setTitle(ILI9341_BLACK,color,4, "     COMPLETED         ");
    _tft->setTextColor(ILI9341_BLACK,color);
    
    
    // Stop reason
    _tft->setCursor(24, LINE(2));   
    _tft->myDrawString(s);
    // Display cap
    float f=_config->sumMa;
    f/=3600.;
    sprintf(buffer,"Cap : %04d mA",(int)f);
    _tft->setFontSize(TFT_eSPI_extended::BigFont);
    _tft->setCursor(4, LINE(0));   
    _tft->myDrawString(buffer);
    
    // Duration
    _tft->setFontSize(TFT_eSPI_extended::MediumFont);

    int mn=_config->duration;
    int h;
    h=mn/60;
    mn-=h*60;
    sprintf(buffer,"Dur : %d:%d mn",h,mn);
    _tft->setCursor(24, LINE(3));    
    _tft->myDrawString(buffer);

}
// EOF