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
                           idleScreen(   batConfig *c);
                      void draw();
        virtual batScreen *process(const CurrentState &s); // return NULL if the current screen stays the same
        

};