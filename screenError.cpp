/***************************************************
 Battery Tester
 * GPL v2
 * (c) mean 2018 fixounet@free.fr
 ****************************************************/

#include "screenInclude.h"
#include "screenError.h"
#include "screenIdle.h"
#include "voltage.h"

/**

*/
errorScreen::errorScreen(   batConfig *c,int er) : batScreen(c)
{
    _errorKind=er;
    _loop=0;
}

/**
 */
batScreen *errorScreen::process(int mV,int mA,int currentTime,int leftRight,bool pressed)
{
    drawVoltageAndCurrent(mV,mA);
    if(mV<BAT_DETECT_NOISE_VOLTAGE)
        return new idleScreen(_config);
    
    _loop++;
    if(_loop>20) {draw(ILI9341_YELLOW); _loop=0;}
    if(_loop>10) {draw(ILI9341_ORANGE); }
    return NULL;
}
/**
 */
 
void errorScreen::draw()
{
    draw(ILI9341_ORANGE);
}
/**
 */
void errorScreen::draw(int color)
{
    _tft->setCursor(18, 80);   
    _tft->setTextColor(color,ILI9341_BLACK);  
    switch(_errorKind)
    {
        case ERROR_VOLTAGE_TOO_HIGH:            
            _tft->println("VOLTAGE TOO HIGH");
            break;
        case ERROR_VOLTAGE_TOO_LOW:
            _tft->println("VOLTAGE TOO LOW");
            break;            
        default:
            _tft->println("OTHER ERROR (?)");
            break;
    }
    _tft->setTextColor(ILI9341_WHITE,ILI9341_BLACK);  
}