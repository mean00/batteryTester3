

#pragma once
#include "lnArduino.h"
#include "lnADC.h"

typedef void (adcEngineCb)(void *cookie, lnPin pin, int value);
/**
 * 
 */
class adcEngine
{
public:
        adcEngine()
        {
            _nbPins=0;
        }
        ~adcEngine()
        {

        }
        void add(lnPin pin, adcEngineCb *cb,void *cookie);
        void start();
        void run(void);
protected:
        struct adcPinEntry
        {
            lnPin _pin;
            void  *_cookie;
            adcEngineCb *_cb;
        };
        adcPinEntry _entries[16];
        int         _nbPins;
        lnTimingAdc *_adc;

};