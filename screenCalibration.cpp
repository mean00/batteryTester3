/***************************************************
 Battery Tester
 * GPL v2
 * (c) mean 2018 fixounet@free.fr
 ****************************************************/

#include "screenInclude.h"
#include "voltage.h"
#include "screenCalibration.h"
#include "ad_timer.h"
#include "simplerMCP4725.h"
#include "simpler_INA219.h"

extern batScreen *spawnNewDischarging(batConfig *c, int mV);

batScreen *spawnNewCalibration(batConfig *c)
{
    return new calibrationScreen(c);
}


/**
 * 
 * @return 
 */
calibrationScreen::calibrationScreen(batConfig *c) : batScreen(c)
{
    _config->mcp->setVoltage(0); 
    voltage1=voltage2=0;
    amp1=amp2=0;
}
/**
 * 
 */
calibrationScreen::~calibrationScreen()
{
    
    
}
/**
 * 
 * @param mV
 * @param mA
 */
void calibrationScreen::calibrate()
{
     // got it
    float deltaVoltage=voltage1-voltage2;
    float deltaAmp=amp2-amp1;

    if(deltaVoltage>_config->batteryDrop) deltaVoltage-=_config->batteryDrop;  // assume a 50mv Drop by the battery itself
    
    float r=(deltaVoltage)/deltaAmp;
    r=r*1000.;
    _config->resistor1000=r;
#if 0
    _config->tft->drawNumber(_config->resistor1000,50,120,4);
    _config->tft->drawNumber((int)deltaVoltage,50,50,4);
    _config->tft->drawNumber((int)deltaAmp,50,70,4);
    delay(10000);
#endif
}

static int getCommand(int v)
{
    return v * 1.28 + 1525.;
}
#define OVERSAMP 8
/**
 */
batScreen *calibrationScreen::process(const CurrentState &s)
{     
    // Prepare
            _config->mcp->setVoltage(getCommand(CALIBRATION_AMP1)); 
            drawVoltageAndCurrent(s);
            xDelay(50);
            voltage1=0;
            amp1=0;
            for(int i=0;i<OVERSAMP;i++)
            {
                voltage1+=_config->ina219->getBusVoltage_V()*1000.;
                amp1+=_config->ina219->getCurrent_mA();
                xDelay(5);
            }
            voltage1/=OVERSAMP;
            amp1/=OVERSAMP;
            
            _config->mcp->setVoltage(getCommand(CALIBRATION_AMP2)); 
            xDelay(50);
            voltage2=0;
            amp2=0;
            for(int i=0;i<OVERSAMP;i++)
            {
                voltage2+=_config->ina219->getBusVoltage_V()*1000.;
                amp2+=_config->ina219->getCurrent_mA();
                xDelay(5);
            }
            voltage2/=OVERSAMP;
            amp2/=OVERSAMP;                      
            // set gate to 0
            _config->mcp->setVoltage(0); 
            calibrate();
            xDelay(100);
            return  spawnNewDischarging(_config,voltage1);
}
/**
 */
void calibrationScreen::draw()
{
    setTitle(ILI9341_BLACK,ILI9341_WHITE,4, "    CALIBRATION      ");
    _tft->setTextColor(ILI9341_WHITE,ILI9341_BLACK);  
    
}
