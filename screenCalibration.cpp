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
    
    float r=(deltaVoltage)/deltaAmp;
    r=r*1000.;
    r-=_config->userSettings.resistor1000;
    if(r<0) r=0;
    
    _config->userSettings.resistor1000=r;
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
#define OVERSAMP 4


void calibrationScreen::sample(int cmd,int &a, int &v)
{
    a=0;
    v=0;
     _config->mcp->setVoltage(getCommand(cmd));
     xDelay(500);
    for(int i=0;i<OVERSAMP;i++)
    {
        int ma,mv;
        mv=_config->ina219->getBusVoltage_V()*1000.;
        ma=_config->ina219->getCurrent_mA();
       
        v+=mv;
        a+=ma;
        xDelay(50);
    }
    v/=OVERSAMP;
    a/=OVERSAMP;
    
    Serial1.print("V: ");
    Serial1.print(v);
    Serial1.print("A: ");
    Serial1.println(a);
}

batScreen *calibrationScreen::process()
{     
#if 0
    sample(200,amp1,voltage1);
    sample(500,amp2,voltage2);            
    // set gate to 0
    _config->mcp->setVoltage(0); 
    calibrate();
    char st[80];
    sprintf(st,"V=%d A=%d",voltage1,amp1);
    _tft->setCursor(30,80);
    _tft->myDrawString(st);

    sprintf(st,"V=%d A=%d",voltage2,amp2);
    _tft->setCursor(30,120);
    _tft->myDrawString(st);

    sprintf(st,"R=%d ",_config->resistor1000);
    _tft->setCursor(30,170);
    _tft->myDrawString(st);
    xDelay(2000);
#endif
    return  spawnNewDischarging(_config,voltage1);
}
/**
 */
void calibrationScreen::draw()
{
    setTitle(ILI9341_BLACK,ILI9341_WHITE,4, "    CALIBRATION      ");
    _tft->setTextColor(ILI9341_WHITE,ILI9341_BLACK);  
    
}
