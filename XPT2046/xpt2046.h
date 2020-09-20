
#pragma once
#include "SPI.h"



/**
 * 
 */
class XPT2046
{
public:    
                     XPT2046(SPIClass &spi, int cs,int speed);
            virtual  ~XPT2046();
            bool     setup();
            bool     run();
    
protected:
        SPIClass &mSPI;    
        int      mCs;
        int      mFrequency;
        SPISettings mSettings;
        int         mRawData[20];
        int         median(int a, int b, int c,int d);
};

// EOF