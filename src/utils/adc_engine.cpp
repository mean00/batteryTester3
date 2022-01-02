#include "adc_engine.h"
/**
 * 
 */
void adcEngine::add(lnPin pin, adcEngineCb *cb,void *cookie)
{
    adcPinEntry *e=_entries +_nbPins++;
    xAssert(_nbPins<=16);
    e->_pin=pin;
    e->_cookie=cookie;
    e->_cb=cb;
}
/**
 * 
 * 
 */
  
static void trampoline(void *a)
{
    adcEngine *m=(adcEngine *)a;
    m->run();
}
/**
 * 
 */
void adcEngine::start()
{
    xTaskCreate(trampoline, "ADCEngine",512,this,5,NULL);
}
#define NB 10
/**
 * 
 */
void adcEngine::run()
{
    _adc=new lnTimingAdc(0);
    lnPin pins[16];
    for(int i=0;i<_nbPins;i++)
        pins[i]=_entries[i]._pin;
    int fq=1000/50; // 50 ms
    _adc->setSource(3,3,fq,_nbPins,pins); // every 50 ms
    uint16_t capture[NB*_nbPins];
    while(1)
    {
            _adc->multiRead(NB,capture);
            for(int i=0;i<_nbPins;i++)
            {
                uint16_t *p=capture+i;
                int sum=0;
                for(int j=0;j<NB;j++)
                {
                    sum+=*p;
                    p+=_nbPins;
                }
                sum=(sum+NB/2)/NB;
                _entries[i]._cb(_entries[i]._cookie,_entries[i]._pin,sum);
            }

    }
}

