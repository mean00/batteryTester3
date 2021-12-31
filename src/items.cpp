/***************************************************
 Battery Tester
 * GPL v2
 * (c) mean 2018 fixounet@free.fr
 ****************************************************/

#include "screenInclude.h"
#include "voltage.h"
#include "screenSetup.h"
#include "screenSetup_internal.h"

#define ITEM_HEIGHT_PIXEL 40
#define ITEM_HEIGHT_OFFSET 38

int itemPosition(int x)
{
    return ITEM_HEIGHT_OFFSET+x*ITEM_HEIGHT_PIXEL;
}


void Item::drawBoundingRectangle()
{
   int color=ILI9341_BLACK;
      if(_state==StateSelected) color=ILI9341_WHITE;
#define BORDER 4
      item_tft->drawRoundRect(16-BORDER,_line-BORDER,
                          320-12*2,ITEM_HEIGHT_PIXEL-2+BORDER,
                              4,color);
      
}
/**
 */
 TunableItem::TunableItem(  TFT_eSPI *tft,int line,int *value, int mn, int mx, int inc, const char *name, const char *unit) : Item(tft,line)
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
  void    TunableItem::drawItem()
  {
      item_tft->setCursor(20, _line);   
      item_tft->myDrawString(_name);
      update();
      drawBoundingRectangle();      
      
  }
  void    TunableItem::update()
  {
      int bg,fg;
      switch(_state)
      {
        default:
        case StateNormal: 
        case StateSelected:
                     item_tft->setTextColor(ILI9341_WHITE,ILI9341_BLACK);  
                     break;
        case StateActivated:
                     item_tft->setTextColor(ILI9341_BLACK,ILI9341_WHITE);  
                     break;
      }
#define ITEM_COLUMN (160+24)
      myBoundPrettyPrint(item_tft,*_value,160+24,_line,_unit,item_tft->width()-ITEM_COLUMN-11);
      item_tft->setTextColor(ILI9341_WHITE,ILI9341_BLACK);  
  }
 
 /**
  */
  void    SimpleItem::drawItem()
  {
      item_tft->setCursor(20, _line);   
      item_tft->myDrawString(_name);      
      drawBoundingRectangle();           
      
  }