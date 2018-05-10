/***************************************************
 Battery Tester
 * GPL v2
 * (c) mean 2018 fixounet@free.fr
 ****************************************************/

#include "screenInclude.h"
#include "voltage.h"
#include "screenSetup.h"
#include "screenSetup_internal.h"
/**
 */
 TunableItem::TunableItem(int line,int *value, int mn, int mx, int inc, const char *name, const char *unit)
 {
     _min=mn;
     _max=mx;
     _inc=inc;
     _value=value;
     _name=name;
     _unit=unit;
     _line=line;

 }
/**
 */
 void TunableItem::run(int leftright)
 {
     if(leftright)
     {
        *_value+=leftright*_inc;
        if(*_value>_max) *_value=_max;
        if(*_value<_min) *_value=_min;
        update();
     }
 }
 /**
  */
  void    TunableItem::draw()
  {
  }
  void    TunableItem::update()
  {
      
  }
 
 
   

TunableItem *item;
/**

*/
setupScreen::setupScreen(   batConfig *c) : batScreen(c)
{
        item=new TunableItem(60,&(_config->targetDischargeMa), 100, 1500,100, "Discharge","A");
}
setupScreen::~setupScreen()
{
    delete item;
    item=NULL;
}
/**
 */
batScreen *setupScreen::process(int mV,int mA,int currentTime,int leftRight,bool pressed)
{
    if(leftRight)
    {
        item->run(leftRight);
    }
    return NULL;        
}
/**
 */
void setupScreen::draw()
{
    item->draw();
}