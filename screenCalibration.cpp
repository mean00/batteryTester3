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

extern batScreen *spawnNewDischarging(batConfig *c, int mV);

batScreen *spawnNewCalibration(batConfig *c)
{
    return new calibrationScreen(c);
}


/**
 * 
 * @return 
 */
calibrationScreen::calibrationScreen(batConfig *c) : batScreen(c),waitTimer(1)
{
    
    state=Calibration_init;
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
    r=r*1000;
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

/**
 */
batScreen *calibrationScreen::process(int mV,int mA,int currentTime,int leftRight,bool pressed)
{    
    if(state==Calibration_init)
    {        
        // set gate to 200 mA
        _config->mcp->setVoltage(getCommand(CALIBRATION_AMP1)); 
        waitTimer.reset();
        drawVoltageAndCurrent(mV,mA);
        state=Calibration_point1;
        return NULL;        
    }
    drawVoltageAndCurrent(mV,mA);
    if(!waitTimer.rdv())
        return NULL;
    switch(state)
    {
        case Calibration_point1:
            voltage1=mV;
            amp1=mA;
            waitTimer.reset();
            _config->mcp->setVoltage(getCommand(CALIBRATION_AMP2)); 
             state=Calibration_point2;
             return NULL;
             break;
        case Calibration_point2:
            voltage2=mV;
            amp2=mA;            
            // set gate to 0
            _config->mcp->setVoltage(0); 
            calibrate();
            delay(100);
            return  spawnNewDischarging(_config,voltage1);
            break;
    default:
            return NULL;
    }
    return NULL;
}
/**
 */
void calibrationScreen::draw()
{
    setTitle(ILI9341_BLACK,ILI9341_WHITE,4, "    CALIBRATION      ");
    _tft->setTextColor(ILI9341_WHITE,ILI9341_BLACK);  
    
}
