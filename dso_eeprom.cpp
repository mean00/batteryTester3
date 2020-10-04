/***************************************************
 STM32 duino based firmware for DSO SHELL/150
 *  * GPL v2
 * (c) mean 2019 fixounet@free.fr
 ****************************************************/
#include "EEPROM.h"
#include "dso_eeprom.h"
#define CURRENT_HASH 0xBEF0
uint16_t calibrationHash;

#define FINE_TUNE_OFFSET 64
#if 0
    #define CHECK_READ(x) xAssert(x)
#else
    #define CHECK_READ(x) if(!(x)) return false;
#endif

int    DSOEeprom::calibration[8]; // top left top right bottom left bottom right (x,y)

bool readValue(EEPROMClass &e2, int offset,int *value)
{
    uint16_t v;
    CHECK_READ(EEPROM_OK==e2.read(2+offset,&v));
    *value=v;
    return true;
}

/**
 * 
 * @return 
 */
bool  DSOEeprom::read()
{
    EEPROMClass e2;
    e2.init();
    calibrationHash=e2.read(0);
    if(calibrationHash!=CURRENT_HASH)
    {
        return false;
    }
    for(int i=0;i<8;i++)
    {
        if(!readValue(e2,i,&(DSOEeprom::calibration[i])))
            return false;
    }
    return true;
}
/**
 * 
 * @return 
 */
bool  DSOEeprom::write()
{
    EEPROMClass e2;
    e2.init();
    e2.format();
    e2.write(0,CURRENT_HASH);
    calibrationHash=e2.read(0);
    for(int i=0;i<8;i++)
        e2.write(2+i,calibration[i]);
    return true;
}
/**
 * 
 * @return 
 */
bool  DSOEeprom::wipe()
{
    EEPROMClass e2;
    e2.init();
    e2.format();
    e2.write(0,0);  
    return true;
}

