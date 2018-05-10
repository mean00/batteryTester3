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
                    Item() {}
    virtual         ~Item() {}
    virtual void    setState(ItemState state) {_state=state;}
    virtual void    run(int leftright) {};
    virtual void    draw()=0;    
protected:
  ItemState         _state;
};

//----------------

class TunableItem : public Item
{
public:
                TunableItem(int line,int *value, int mn, int mx, int inc, const char *name, const char *unit);                      
        void    draw();
        void    update();
        void    run(int leftright);
protected:
            int _min,_max,_inc;
            int *_value;
            int _line;
            const char *_name,*_unit;
};
