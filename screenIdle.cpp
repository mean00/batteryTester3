/***************************************************
 Battery Tester
 * GPL v2
 * (c) mean 2018 fixounet@free.fr
 ****************************************************/

#include <Wire.h>
#include "SPI.h"
#include "Adafruit_GFX_AS.h"
#include "Adafruit_ILI9341_STM.h"
#include "screenIdle.h"
#include "backgrounds/background.h"
#include "backgrounds/li_ion.h"
#include "Adafruit_MCP4725.h"
#include "voltage.h"
#include "screenError.h"
extern Adafruit_MCP4725     *mcp4725;

/**

*/
idleScreen::idleScreen(   batConfig *c,Adafruit_ILI9341_STM *tft) : batScreen(c,tft)
{

}
/**
 */
batScreen *idleScreen::process(int mV,int mA,int currentTime,int leftRight,bool pressed)
{
    drawVoltageAndCurrent(mV, mA);
    if(mV<BAT_DETECT_NOISE_VOLTAGE)
        return NULL;
    
    if(mV>BAT_DETECT_MAX_VOLTAGE)
        return new errorScreen(_config, _tft,ERROR_VOLTAGE_TOO_HIGH);
    if(mV<BAT_DETECT_MIN_VOLTAGE)
        return new errorScreen(_config,_tft,ERROR_VOLTAGE_TOO_LOW);
    // GO
    return NULL;        
}
/**
 */
void idleScreen::draw()
{
    drawBitmap(296,80,16,64,0xffff,0,li_ion+11);
    
}