/***************************************************
 Battery Tester
 * GPL v2
 * (c) mean 2018 fixounet@free.fr
 ****************************************************/
#pragma once
#include "screenBase.h"

class dischargingScreen : public batScreen
{
public:
                           dischargingScreen(   batConfig *c, int currentV);
                      void draw();
        virtual batScreen *process(int mV,int mA,int currentTime,int leftRight,bool pressed); // return NULL if the current screen stays the same
        
protected:
                bool    evaluateTargetAmp(int currentV);
                int     computeGateCommand(int amp);
};