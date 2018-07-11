/***************************************************
 Battery Tester
 * GPL v2
 * (c) mean 2018 fixounet@free.fr
 ****************************************************/

#include "screenInclude.h"
#include "voltage.h"
#include "screenSetup.h"
#include "screenSetup_internal.h"


extern int itemPosition(int x);

extern batScreen *spawnNewDischarging(batConfig *c, int mV);

/**
 */ 
batScreen  *spawnSetupScreen(   batConfig *c)
{
    return new setupScreen(c);
}
/**
 */
void setupScreen::drawItem()
{
     item_tft->setCursor(20, _line);   
     item_tft->myDrawString("Go!");   
     drawBoundingRectangle();      
}
/**

*/
setupScreen::setupScreen(   batConfig *c) : batScreen(c),Item(c->tft,itemPosition(3))
{
        nbItems=0;
        currentItem=0;
        addItem(new TunableItem(_tft,itemPosition(0),&(_config->targetDischargeMa), 100, 2500,100, "Dischrg","A"));
        addItem(new TunableItem(_tft,itemPosition(1),&(_config->minimumVoltage), 2800, 5000,100, "Min Volt","V"));
        addItem(new TunableItem(_tft,itemPosition(2),&(_config->resistor1000), 100, 1500,100, "Wiring ","O"));
        addItem( this);
        items[nbItems-1]->setState(StateSelected) ;   
        _sstate=StateSelecting;
        currentItem=nbItems-1;
        
}
setupScreen::~setupScreen()
{
    for(int i=0;i<nbItems-1;i++)
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
    drawVoltageAndCurrent(mV,mA);
    switch(_sstate)
    {
    case StateSelecting:
        {
            if(leftRight)
            {
                Item *old=items[currentItem];
                if(leftRight>0)
                {
                    currentItem++;
                    if(currentItem>=nbItems) currentItem=nbItems-1;
                }else if(leftRight<0)
                {
                    currentItem--;
                    if(currentItem<0) currentItem=0;
                }

                Item *nw=items[currentItem];
                old->setState(StateNormal);
                nw->setState(StateSelected);
                old->drawItem();
                nw->drawItem();
                return NULL;
            }
            if(pressed)
            {
                if(items[currentItem]==this)
                    return spawnNewDischarging(_config,mV);
                _sstate=StateEditing;
                items[currentItem]->setState(StateActivated);
                items[currentItem]->drawItem();
                return NULL;
            }
            return NULL;
        }
        break;
    case StateEditing:
      {
        if(pressed)
        {
            _sstate=StateSelecting;
            items[currentItem]->setState(StateSelected);
            items[currentItem]->drawItem();
            return NULL;
        }
        if(leftRight)
        {
            items[currentItem]->run(leftRight);
        }
        break;
      }
    default:
        break;
    }
    return NULL;
}
/**
 */
void setupScreen::draw()
{
    _tft->setTextColor(ILI9341_BLACK,ILI9341_WHITE);  
    _tft->setCursor(4, 4);   
    _tft->myDrawString("           SETUP           ");    
    _tft->setTextColor(ILI9341_WHITE,ILI9341_BLACK);  
    
    for(int i=0;i<nbItems;i++)
    {
        items[i]->drawItem();
    }
}