/***************************************************
 Battery Tester
 * GPL v2
 * (c) mean 2018 fixounet@free.fr
 ****************************************************/

#pragma once
#include "embedded_printf/printf.h"
/**

*/
#include "settings.h"
#include "TFT_eSPI_stm32duino.h"
class myMCP4725;
class WavRotary;
class simpler_INA219;
/**
 */
class batConfig
{
public:    
    UserSettings    userSettings;
    
    uint32_t        duration;
    float           sumMa;
    int             targetDischargeMa;
    int             currentDischargeMa;
    TFT_eSPI        *tft;
    myMCP4725       *mcp;
    WavRotary       *rotary;
    simpler_INA219  *ina219;
    int             batteryResistance;
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
        virtual batScreen *process()=0; // return NULL if the current screen stays the same
protected:
                void prettyPrint(int val,int x,int y,const char *unit);
                void drawVoltageAndCurrent(const CurrentState &s);
                void drawBackground();
                void drawBitmap(int width, int height, int wx, int wy, int fgcolor, int bgcolor, const uint8_t *data);
                void disableCurrent();
                void setTitle(int color, int bgColor,int x, const char *title);
                bool readState(CurrentState &s);
protected:
        batConfig *_config;
        TFT_eSPI   *_tft;
};

void myPrettyPrint(TFT_eSPI *tft,int val,int x,int y,const char *unit);
void myBoundPrettyPrint(TFT_eSPI *_tft,int val,int x,int y,const char *unit, int maxWidth);

batScreen  *spawnSetupScreen(   batConfig *c);
// EOF
