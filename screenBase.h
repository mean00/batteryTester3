/***************************************************
 Battery Tester
 * GPL v2
 * (c) mean 2018 fixounet@free.fr
 ****************************************************/

#pragma once
#include "ILI9341_extended.h"
/**

*/
class Adafruit_MCP4725;
typedef struct batConfig
{
    int     resistor1000; // 1000x the wiring resistor
    uint32_t duration;
    float    sumMa;
    int     currentDischargeMa;
    int     targetDischargeMa;
    int     minimumVoltage;
    int     batteryDrop;
    ILI9341  *tft;
    Adafruit_MCP4725 *mcp;
};
/**

*/
class batScreen
{
public:
        batScreen(   batConfig *c)
        {
            _config=c;
            _tft=c->tft;
            drawBackground();
            disableCurrent();
        } 
        virtual ~batScreen()
        {
            _config=NULL;
            _tft=NULL;
        }
        virtual void      draw()=0;
        virtual batScreen *process(int mV,int mA,int currentTime,int leftRight,bool pressed)=0; // return NULL if the current screen stays the same
protected:
                void prettyPrint(int val,int x,int y,const char *unit);
                void drawVoltageAndCurrent(int mV, int mA);
                void drawBackground();
                void drawBitmap(int width, int height, int wx, int wy, int fgcolor, int bgcolor, const uint8_t *data);
                void disableCurrent();
protected:
        batConfig *_config;
        ILI9341   *_tft;
};

void myPrettyPrint(ILI9341 *tft,int val,int x,int y,const char *unit);


batScreen  *spawnSetupScreen(   batConfig *c);
// EOF
