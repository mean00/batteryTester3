/***************************************************
 Battery Tester
 * GPL v2
 * (c) mean 2018 fixounet@free.fr
 ****************************************************/
#pragma once
#include "screenBase.h"
#include "ad_timer.h"
//----------------

#define CALIBRATION_AMP1 200 // do calibration at 100 mA
#define CALIBRATION_AMP2 500 // do calibration at 250 mA

/**
 * 
 * @param c
 */
class calibrationScreen : public batScreen
{
public:
  
                           calibrationScreen(   batConfig *c);
virtual                   ~calibrationScreen();                        
                      void draw();
        virtual batScreen *process(const CurrentState &s); // return NULL if the current screen stays the same
        
protected:   
                    int     voltage1,voltage2,amp1,amp2;
                    void    calibrate();
                    void    sample(int cmd,int &a, int &v);
};