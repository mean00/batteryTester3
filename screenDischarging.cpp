/***************************************************
 Battery Tester
 * GPL v2
 * (c) mean 2018 fixounet@free.fr
 ****************************************************/

#include "screenInclude.h"
#include "screenDischarging.h"
#include "screenError.h"
#include "voltage.h"
#include "Adafruit_MCP4725.h"
#define SAMPLING_PERIOD 5 // Refresh every 10 sec

#define DEBUG
/**

*/
dischargingScreen::dischargingScreen(   batConfig *c,int currentMv) : batScreen(c),timer(SAMPLING_PERIOD)
{
    _config->sumMa=0;
    evaluateTargetAmp(currentMv);
    gateCommand=computeGateCommand(_config->currentDischargeMa);
    _config->mcp->setVoltage(gateCommand,false);
}
/**
 */
batScreen *dischargingScreen::process(int mV,int mA,int currentTime,int leftRight,bool pressed)
{
    drawVoltageAndCurrent(mV, mA);
    if(mA<_config->currentDischargeMa/2)
    {
        
    }
    if(mV<_config->minimumVoltage)
    {
        
    }
    if(!timer.rdv()) return NULL;
    // update sumA
    _config->sumMa+=SAMPLING_PERIOD*mA;
    timer.nextPeriod();
   
    updateInfo();
    return NULL;
    
}

void dischargingScreen::updateInfo()
{
    int mn,sec,h;
    char buffer[200];
    
     
    timer.wallClock(mn,sec);
    _tft->setTextColor(ILI9341_WHITE,ILI9341_BLACK);          
    
    float c=_config->sumMa;
    c/=3600.;
    
    sprintf(buffer,"%04d mA/h ",(int)c); // 10 sec -> hour
    _tft->setCursor(18, 60);       
    _tft->println(buffer);
    
    h=mn/60;
    mn-=h*60;
    sprintf(buffer,"%02d:%02d:%02d",h,mn,sec);
    _tft->setCursor(18, 80);       
    _tft->println(buffer);
}

/**
 */
void dischargingScreen::draw()
{   
    char buffer[200];
    _tft->setTextColor(ILI9341_WHITE,ILI9341_BLACK);      
    _tft->setCursor(24, 8);       
    _tft->println("Discharging");
    updateInfo();
    _tft->setCursor(24, 160);       
    sprintf(buffer,"Target = %d mA",_config->currentDischargeMa);
    _tft->println(buffer);
    _tft->setCursor(24, 160-24);       
#ifdef DEBUG    
    sprintf(buffer,"Gate = %d ",gateCommand);
   _tft->println(buffer);
#endif
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
        _config->currentDischargeMa=50+100*floor(maxAmp/100);
    else
        _config->currentDischargeMa=_config->targetDischargeMa;
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