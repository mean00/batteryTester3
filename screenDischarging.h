/***************************************************
 Battery Tester
 * GPL v2
 * (c) mean 2018 fixounet@free.fr
 ****************************************************/
#pragma once
#include "screenBase.h"
#include "screenFinished.h"
#include "ad_timer.h"

class dischargingScreen : public batScreen
{
public:
                           dischargingScreen(   batConfig *c, int currentV);
                      void draw();
        virtual batScreen *process(int mV,int mA,int currentTime,int leftRight,bool pressed); // return NULL if the current screen stays the same
        
protected:
                bool    evaluateTargetAmp(int currentV);
                int     computeGateCommand(int amp);
                void    updateInfo();
                Timer   timer;
                int     gateCommand;
                batScreen *goToEnd(EndOfChargeCause cause); 
};