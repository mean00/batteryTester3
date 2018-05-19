/***************************************************
 Battery Tester
 * GPL v2
 * (c) mean 2018 fixounet@free.fr
 ****************************************************/
#pragma once
#include "screenBase.h"
#include "screenSetup_internal.h"
//----------------


/**
 */
class setupScreen : public batScreen,Item
{
public:
        enum ScreenState
        {
          StateSelecting,
          StateEditing
        };
  
                           setupScreen(   batConfig *c);
virtual                   ~setupScreen();                        
                      void draw();
                      void drawItem();
        virtual batScreen *process(int mV,int mA,int currentTime,int leftRight,bool pressed); // return NULL if the current screen stays the same
        
protected:        
            Item *items[10];
            int   nbItems;
            void  addItem(Item *item);
            int   currentItem;
            ScreenState _sstate;
};