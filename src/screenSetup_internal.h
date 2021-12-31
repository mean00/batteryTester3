/***************************************************
 Battery Tester
 * GPL v2
 * (c) mean 2018 fixounet@free.fr
 ****************************************************/
#pragma once

//----------------
enum ItemState
{
  StateNormal,
  StateActivated,
  StateSelected
};

//----------------
class Item
{
public:
                    Item(  TFT_eSPI *tft,int line) {item_tft=tft;_line=line;_state=StateNormal;}
    virtual         ~Item() {}
    virtual void    setState(ItemState state) {_state=state;}
    virtual void    run(int leftright) {};
    virtual void    drawItem()=0;    
    virtual void    drawBoundingRectangle();
protected:
  ItemState         _state;  
  TFT_eSPI          *item_tft;
  int               _line;
};
//
class SimpleItem : public Item
{
public:
                    SimpleItem(  TFT_eSPI *tft, int line,const char *name ) : Item(tft,line) {_name=name;}
    virtual         ~SimpleItem() {}    
    virtual void    run(int leftright) {};
    virtual void    drawItem();    
protected:
    const char *_name;
};

//----------------

class TunableItem : public Item
{
public:
                TunableItem(TFT_eSPI *tft,int line,int *value, int mn, int mx, int inc, const char *name, const char *unit);                      
        void    drawItem();
        void    update();
        void    run(int leftright);
protected:
            int _min,_max,_inc;
            int *_value;
            const char *_name,*_unit;
            
};
