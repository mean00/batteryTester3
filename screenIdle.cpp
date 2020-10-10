/***************************************************
 Battery Tester
 * GPL v2
 * (c) mean 2018 fixounet@free.fr
 ****************************************************/

#include "screenInclude.h"
#include "screenIdle.h"
#include "backgrounds/generated/li_ion_decl.h"

#include "voltage.h"
#include "screenError.h"

/**

*/
idleScreen::idleScreen(   batConfig *c) : batScreen(c)
{

}
/**
 */
batScreen *idleScreen::process(const CurrentState &s)
{
    drawVoltageAndCurrent(s);
    if(s.mVoltage<BAT_DETECT_NOISE_VOLTAGE)
        return NULL;
    
    if(s.mVoltage>BAT_DETECT_MAX_VOLTAGE)
        return new errorScreen(_config, ERROR_VOLTAGE_TOO_HIGH);
    if(s.mVoltage<BAT_DETECT_MIN_VOLTAGE)
        return new errorScreen(_config,ERROR_VOLTAGE_TOO_LOW);
    return spawnSetupScreen(_config);        
}
/**
 */
void idleScreen::draw()
{
    drawBitmap(li_ion_width,li_ion_height,10,64,0,ILI9341_YELLOW,li_ion);
    
}