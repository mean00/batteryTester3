/***************************************************
 Battery Tester
 * GPL v2
 * (c) mean 2018 fixounet@free.fr
 *****************************************************/
#include "xpt2046.h"
#include "TFT_eSPI_extended.h"
#include "dso_eeprom.h"
#include "dso_debug.h"
/**
 * 
 * @param x
 * @param t
 */
class calibration
{
public:
        calibration(XPT2046 *x, TFT_eSPI_extended *t)
        {
            xpt=x;
            tft=t;
            
        }
        bool calibrate()
        {
            singlePoint(25,25,          calibrationData+0,  calibrationData+1);
            xDelay(2000);
            singlePoint(320-25,25,      calibrationData+2,  calibrationData+3);
            xDelay(2000);
            singlePoint(320-25,240-25,  calibrationData+4,  calibrationData+5);
            xDelay(2000);
            singlePoint(25,240-25,      calibrationData+6,  calibrationData+7);

            for(int i=0;i<8;i++)
                Logger("CAL %d: %d\n",i,calibrationData[i]);

            DSOEeprom::setValue(calibrationData);    
            DSOEeprom::write();
            Logger("Calibration done\n");    
        }

        /**
         * 
         * @param posx
         * @param posy
         * @param touchX
         * @param touchY
         */
        void singlePoint(int posx,int posy, int *touchX,int *touchY)
        {
            tft->fillScreen(ILI9341_BLACK);

            tft->setCursor(100,100);
            tft->myDrawString("Calibration");

            tft->fillCircle(posx,posy,8,ILI9341_GREEN);
            int count=0;
            int x=0,y=0;
            *touchX=0;
            *touchY=0;


            int skip=5;
            while(skip--)
                while(!xpt->rawRead(x,y)) // skip 1st
                {
                  xDelay(50);
                }
            while(count<8)
            {
                if(xpt->rawRead(x,y))
                {
                    Logger("Raw X:%d Y:%d\n",x,y);
                    *touchX+=x; // SWAP x & y
                    *touchY+=y;
                    count++;
                    xDelay(100);
                }
            } 
            *touchX>>=3;
            *touchY>>=3;
            tft->fillScreen(ILI9341_BLACK);

        }
protected:
           XPT2046 *xpt;
           TFT_eSPI_extended *tft;
           int      calibrationData[8];
};

/**
 * 
 */
void touchCalibration(XPT2046 *xpt, TFT_eSPI_extended *tft)
{
  calibration c(xpt,tft);
  c.calibrate();  
}
    
//--


