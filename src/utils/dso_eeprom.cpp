/***************************************************
 STM32 duino based firmware for DSO SHELL/150
 *  * GPL v2
 * (c) mean 2019 fixounet@free.fr
 ****************************************************/
#include "EEPROM.h"
#include "dso_eeprom.h"

uint16_t calibrationHash;

#define CUSTOM_START 20
#define CURRENT_HASH 0xBEF1

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
 * @param value
 * @return 
 */
bool DSOEeprom::read(int dex,int &value)
{
    EEPROMClass e2;
    e2.init();
    calibrationHash=e2.read(0);
    if(calibrationHash!=CURRENT_HASH)
    {
        return false;
    }
    if(!readValue(e2,dex*2+CUSTOM_START,&value))
        return false;
    return true; 
}
/**
 * 
 * @param value
 * @return 
 */
bool DSOEeprom::write(int dex,int &value)
{
    EEPROMClass e2;
    e2.init();
    if(FLASH_COMPLETE==e2.update(2+dex*2+CUSTOM_START,value))
        return true;
    return false;
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

