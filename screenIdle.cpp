#include <Wire.h>
#include "SPI.h"
#include "Adafruit_GFX_AS.h"
#include "Adafruit_ILI9341_STM.h"
#include "screenIdle.h"
/**

*/
idleScreen::idleScreen(   batConfig *c,Adafruit_ILI9341_STM *tft) : batScreen(c,tft)
{

}
batScreen *idleScreen::process(int mV,int mA,int currentTime,int leftRight,bool pressed)
{
    
}
void idleScreen::draw()
{
    
}