/***************************************************
 Battery Tester
 * GPL v2
 * (c) mean 2018 fixounet@free.fr
 ****************************************************/

#pragma once

/**

*/
#include "TFT_eSPI_extended.h"
class myMCP4725;
class WavRotary;
typedef struct batConfig
{
    int     resistor1000; // 1000x the wiring resistor
    uint32_t duration;
    float    sumMa;
    int     currentDischargeMa;
    int     targetDischargeMa;
    int     minimumVoltage;
    int     batteryDrop;
    TFT_eSPI_extended  *tft;
    myMCP4725 *mcp;
    WavRotary *rotary;
};


class CurrentState
{
public:
        int mVoltage;
        int mCurrent;
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
        virtual batScreen *process(const CurrentState &state)=0; // return NULL if the current screen stays the same
protected:
                void prettyPrint(int val,int x,int y,const char *unit);
                void drawVoltageAndCurrent(const CurrentState &s);
                void drawBackground();
                void drawBitmap(int width, int height, int wx, int wy, int fgcolor, int bgcolor, const uint8_t *data);
                void disableCurrent();
                void setTitle(int color, int bgColor,int x, const char *title);
protected:
        batConfig *_config;
        TFT_eSPI_extended   *_tft;
};

void myPrettyPrint(TFT_eSPI_extended *tft,int val,int x,int y,const char *unit);
void myBoundPrettyPrint(TFT_eSPI_extended *_tft,int val,int x,int y,const char *unit, int maxWidth);

batScreen  *spawnSetupScreen(   batConfig *c);
// EOF
