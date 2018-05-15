/***************************************************
 Battery Tester
 * GPL v2
 * (c) mean 2018 fixounet@free.fr
 ****************************************************/

#include "screenInclude.h"
#include "screenDischarging.h"
#include "screenError.h"
#include "voltage.h"
/**

*/
dischargingScreen::dischargingScreen(   batConfig *c,int currentMv) : batScreen(c)
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
batScreen *spawnNewDischarging(batConfig *c, int currentV)
{
    return new dischargingScreen(c,currentV);
}
/**
 * \brief make sure we done exceed MAX_WATT
 * @param currentV
 * @return 
 */
bool     dischargingScreen::evaluateTargetAmp(int currentV)
{
    // current V cannot be zero ! 800 mV at least
    float maxAmp=(1000.*1000.*BAT_MAX_WAT)/(float)currentV; // in mA
    if(maxAmp<_config->targetDischargeMa)
        _config->targetDischargeMa=50+100*floor(maxAmp/100);
    return true;
}
/**
 * \brief Compute the value to send to the DAC driving the IRLZ44N so that we have the wanted 
 * current
 * @param amp
 * @return 
 */
int     dischargingScreen::computeGateCommand(int amp)
{
    // Command=1.38*a+1443
    float v=amp;
    v=v*1.38+1443.;
    if(v>4095) v=4095;
    return (int)v;
}

// EOF