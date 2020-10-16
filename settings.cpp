/***************************************************
 Battery Tester
 * GPL v2
 * (c) mean 2018 fixounet@free.fr
 ****************************************************/

#include <Wire.h>
#include "SPI.h"
#include "settings.h"
#include "dso_eeprom.h"
 


#define WIRE_RESISTANCE_INDEX           0
#define DISCHARGE_CURRENT_INDEX         1
#define MIN_VOLTAGE_INDEX               2

#define WIRE_RESISTANCE_DEFAULT         201
#define DISCHARGE_CURRENT_DEFAULT       501
#define MIN_VOLTAGE_DEFAULT             3001


/**
 * 
 */
void    UserSettings::loadSettings()
{
    int v;        
#define LOAD(x,y) {if(DSOEeprom::read(x##_INDEX,v))  {y=v;}else{y=x##_DEFAULT;}}
    
    LOAD(WIRE_RESISTANCE,resistor1000);
    LOAD(DISCHARGE_CURRENT,initialDischargeMa);
    LOAD(MIN_VOLTAGE,minimumVoltage);    
}
/**
 * 
 */
void    UserSettings::saveSettings()
{
    int v;        
#define SAVE(x,y) {v=-1;DSOEeprom::read(x##_INDEX,v);  {if(y!=v) DSOEeprom::write(x##_INDEX,y);}}
    
    SAVE(WIRE_RESISTANCE,resistor1000);
    SAVE(DISCHARGE_CURRENT,initialDischargeMa);
    SAVE(MIN_VOLTAGE,minimumVoltage);    
}

//--EOF
