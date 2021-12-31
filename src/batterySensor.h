#include "simpleADC.h"

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
            simpleAdc    *_adc;
            int           _pinV, _pinA;
            float         _vcc;
            float         _voltage,_current;
            
protected:
            
};

// EOF