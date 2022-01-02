/***************************************************
 Battery Tester
 * GPL v2
 * (c) mean 2018 fixounet@free.fr
 ****************************************************/
#pragma once
#include "screenBase.h"


enum EndOfChargeCause
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
        virtual batScreen *process(); // return NULL if the current screen stays the same
        
protected:
          EndOfChargeCause  _cause;          
};