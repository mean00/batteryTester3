/***************************************************
 Battery Tester
 * GPL v2
 * (c) mean 2018 fixounet@free.fr
 ****************************************************/
#pragma once
#include "screenBase.h"
class idleScreen : public batScreen
{
public:
                           idleScreen(   batConfig *c,Adafruit_ILI9341_STM *tft);
                      void draw();
        virtual batScreen *process(int mV,int mA,int currentTime,int leftRight,bool pressed); // return NULL if the current screen stays the same
};