/***************************************************
 STM32 duino based firmware for DSO SHELL/150
 *  * GPL v2
 * (c) mean 2019 fixounet@free.fr
 ****************************************************/
#pragma once
class DSOEeprom
{
public:
        static bool read(int dex,int &value);        
        static bool write(int dex,int &value);
    
        static bool read();        
        static bool write();
        static bool wipe();  
        static bool setValue(int *c) {memcpy(calibration,c,8*sizeof(int));return true;}
static         int    calibration[8]; // top left top right bottom left bottom right (x,y)
};