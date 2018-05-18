/***************************************************
 Battery Tester
 * GPL v2
 * (c) mean 2018 fixounet@free.fr
 ****************************************************/
#pragma once
#include "screenBase.h"


typedef enum EndOfChargeCause
{
        END_CURRENT_LOW,
        END_VOLTAGE_LOW,
        END_CURRENT_HIGH
};

class finishedScreen : public batScreen
{
public:
                           finishedScreen(   batConfig *c, EndOfChargeCause cause);
                      void draw();
        virtual batScreen *process(int mV,int mA,int currentTime,int leftRight,bool pressed); // return NULL if the current screen stays the same
        
protected:
          EndOfChargeCause  _cause;          
};