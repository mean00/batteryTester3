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
 TunableItem::TunableItem(  Adafruit_ILI9341_STM *tft,int line,int *value, int mn, int mx, int inc, const char *name, const char *unit) : Item(tft)
 {
     _min=mn;
     _max=mx;
     _inc=inc;
     _value=value;
     _name=name;
     _unit=unit;
     _line=line;
     _state=StateNormal;

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
      _tft->setCursor(20, _line);   
      _tft->println(_name);
      update();
      int color=ILI9341_BLACK;
      if(_state==StateSelected) color=ILI9341_WHITE;
      _tft->drawRoundRect(16,_line,320-16*2,24,4,color);
      
      
  }
  void    TunableItem::update()
  {
      int bg,fg;
      switch(_state)
      {
        default:
        case StateNormal: 
        case StateSelected:
                     _tft->setTextColor(ILI9341_WHITE,ILI9341_BLACK);  
                     break;
        case StateActivated:
                     _tft->setTextColor(ILI9341_BLACK,ILI9341_WHITE);  
                     break;
      }
      myPrettyPrint(_tft,*_value,160+24,_line,_unit);
      _tft->setTextColor(ILI9341_WHITE,ILI9341_BLACK);  
  }
 
 
   batScreen  *spawnSetupScreen(   batConfig *c)
   {
       return new setupScreen(c);
   }


/**

*/
setupScreen::setupScreen(   batConfig *c) : batScreen(c)
{
        nbItems=0;
        currentItem=0;
        addItem(new TunableItem(_tft,20,&(_config->targetDischargeMa), 100, 1500,100, "Dischrg","A"));
        addItem(new TunableItem(_tft,60,&(_config->minimumVoltage), 2800, 5000,100, "Min Volt","V"));
        items[0]->setState(StateSelected) ;       
        
}
setupScreen::~setupScreen()
{
    for(int i=0;i<nbItems;i++)
        delete items[i];
    nbItems=0;
    
}
void setupScreen::addItem(Item *item)
{
    items[nbItems++]=item;
}


/**
 */
batScreen *setupScreen::process(int mV,int mA,int currentTime,int leftRight,bool pressed)
{    
    if(leftRight)
    {
        items[currentItem]->run(leftRight);
    }
    return NULL;        
}
/**
 */
void setupScreen::draw()
{
    for(int i=0;i<nbItems;i++)
    {
        if(i==currentItem)
            items[i]->setState(StateSelected);
        else
            items[i]->setState(StateNormal);
        items[i]->draw();
    }
}