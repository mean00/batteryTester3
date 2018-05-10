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
 TunableItem::TunableItem(  Adafruit_ILI9341_STM *tft,int line,int *value, int mn, int mx, int inc, const char *name, const char *unit) : Item(tft,line)
 {
     _min=mn;
     _max=mx;
     _inc=inc;
     _value=value;
     _name=name;
     _unit=unit;
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
#define BORDER 4
      _tft->drawRoundRect(16-BORDER,_line-BORDER,
                          320-12*2,25+BORDER,4,color);
      
      
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
 
 /**
  */
  void    SimpleItem::draw()
  {
      _tft->setCursor(20, _line);   
      _tft->println(_name);      
      int color=ILI9341_BLACK;
      if(_state==StateSelected) color=ILI9341_WHITE;
#define BORDER 4
      _tft->drawRoundRect(16-BORDER,_line-BORDER,
                          320-12*2,25+BORDER,4,color);
      
      
  }