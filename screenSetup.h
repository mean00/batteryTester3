/***************************************************
 Battery Tester
 * GPL v2
 * (c) mean 2018 fixounet@free.fr
 ****************************************************/
#pragma once
#include "screenBase.h"
//----------------

class setupScreen : public batScreen
{
public:
                           setupScreen(   batConfig *c);
virtual                   ~setupScreen();                        
                      void draw();
        virtual batScreen *process(int mV,int mA,int currentTime,int leftRight,bool pressed); // return NULL if the current screen stays the same
        

};