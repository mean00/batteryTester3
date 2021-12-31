/***************************************************
 Battery Tester
 * GPL v2
 * (c) mean 2018 fixounet@free.fr
 ****************************************************/
#pragma once
#include "screenBase.h"

enum 
{
  ERROR_VOLTAGE_TOO_HIGH=0,
  ERROR_VOLTAGE_TOO_LOW=1,
};

class errorScreen : public batScreen
{
public:
                           errorScreen(   batConfig *c, int errorKind);
                      void draw();
        virtual batScreen *process(); // return NULL if the current screen stays the same
protected:
        void draw(int color);
        int _errorKind;
        int _loop;
};
