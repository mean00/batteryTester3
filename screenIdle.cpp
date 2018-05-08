#include <Wire.h>
#include "SPI.h"
#include "Adafruit_GFX_AS.h"
#include "Adafruit_ILI9341_STM.h"
#include "screenIdle.h"
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
/**
 */
void batScreen::prettyPrint(int val,int x,int y,const char *unit)
{
     char printBuffer[256];
     char ext[10];
     
     if(val<1000)
     {
         sprintf(printBuffer,"%d m%c",val,unit[0]);
     }else
     {
         float v=val;
         v/=1000.;
         sprintf(printBuffer,"%1.2f %c",v,unit[0]);
     }
     
    _tft->setCursor(x, y);   
    _tft->println(printBuffer);
}