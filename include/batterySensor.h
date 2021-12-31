#include "lnArduino.h"
#include "lnADC.h"


/**
 * 
 * @param pinV
 * @param pinA
 */
class BatterySensor: public xTask
{
public:
                            BatterySensor(int pinV, int pinA);
            bool            rawRead(float &v, float &a);
            bool            getVoltageCurrent(float &v, float &a)
            {
                v=_voltage;
                a=_current;
                return true;
            }
protected:
            bool           readVoltageCurrent(float &volt,float &current);
            void           run();
            lnTimingAdc    *_adc;
            float         _vcc;
            float         _voltage,_current;
            lnPin         _pins[2];
            
protected:
            
};

// EOF