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
        addItem(new SimpleItem(_tft,100,"Go!"));
        items[0]->setState(StateSelected) ;   
        _state=StateSelecting;
        
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
    drawVoltageAndCurrent(mV,mA);
    switch(_state)
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
                old->draw();
                nw->draw();
                return NULL;
            }
            if(pressed)
            {
                _state=StateEditing;
                items[currentItem]->setState(StateActivated);
                items[currentItem]->draw();
                return NULL;
            }
            return NULL;
        }
        break;
    case StateEditing:
      {
        if(pressed)
        {
            _state=StateSelecting;
            items[currentItem]->setState(StateSelected);
            items[currentItem]->draw();
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
    for(int i=0;i<nbItems;i++)
    {
        items[i]->draw();
    }
}