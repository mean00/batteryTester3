/***************************************************
 Battery Tester
 * GPL v2
 * (c) mean 2018 fixounet@free.fr
 ****************************************************/

#include "screenInclude.h"
#include "screenDischarging.h"
#include "screenError.h"

/**

*/
dischargingScreen::dischargingScreen(   batConfig *c) : batScreen(c)
{

}
/**
 */
batScreen *dischargingScreen::process(int mV,int mA,int currentTime,int leftRight,bool pressed)
{
    drawVoltageAndCurrent(mV, mA);
    return NULL;
}
/**
 */
void dischargingScreen::draw()
{
     _tft->setCursor(18, 80);   
    _tft->setTextColor(ILI9341_WHITE,ILI9341_BLACK);      
    _tft->println("Ready !");
    _tft->setTextColor(ILI9341_WHITE,ILI9341_BLACK);  
    
}
/**
 */
batScreen *spawnNewDischarging(batConfig *c)
{
    return new dischargingScreen(c);
}
