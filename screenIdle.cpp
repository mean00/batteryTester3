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
/**

*/
idleScreen::idleScreen(   batConfig *c,Adafruit_ILI9341_STM *tft) : batScreen(c,tft)
{
    _tft->setCursor(10, 50);   
    _tft->println("Volt");

    _tft->setCursor(10, 80);   
    _tft->println("Amp");

}
/**
 */
batScreen *idleScreen::process(int mV,int mA,int currentTime,int leftRight,bool pressed)
{
    prettyPrint(mV,120,50,"V");
    prettyPrint(mA,120,80,"A");
    return NULL;
}
/**
 */
void idleScreen::draw()
{
  
    
}