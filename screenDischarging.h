/***************************************************
 Battery Tester
 * GPL v2
 * (c) mean 2018 fixounet@free.fr
 ****************************************************/
#pragma once
#include "screenBase.h"
#include "screenFinished.h"
#include "ad_timer.h"

#define AVERAGING_SAMPLE_COUNT 10
#define AVERAGING_SAMPLE_PERIOD 100 // 100 ms

#define ANIMATION_MAX 4

class dischargingScreen : public batScreen
{
public:
    enum VOLTAGE_RANGE
    {
        RANGE_HIGH=0,
        RANGE_MED=1,
        RANGE_LOW=2
                
    };
                           dischargingScreen(   batConfig *c, int currentV);
                      void draw();
        virtual batScreen *process(); // return NULL if the current screen stays the same
        
protected:
                bool    evaluateTargetAmp();
                int     computeGateCommand(int amp);
                void    updateInfo();
                bool    resetAverage();
                bool    processEvents();
                int     gateCommand;
                int     originalGateCommand;
                batScreen *goToEnd(EndOfChargeCause cause); 
                bool       computeAverage(int mV,int mA,int &avgV, int &avgA);
                bool       adjustGateVoltage(int avgA,int avgV);
                void       updateTargetCurrent();
                bool       LeftOrRigh(int leftRight);
                void        animate();
                int        sampleIndex;
                int        samplema[AVERAGING_SAMPLE_COUNT];
                int        samplemv[AVERAGING_SAMPLE_COUNT];
                bool       paused;
                VOLTAGE_RANGE range;
                int         resyncing;
                int         animation;
                
                Timer   timer;
                Timer   smallTimer,debounceTimer;
                Timer   animateTimer;
                Timer   tuneTimer;
                
};