#pragma once
/**

*/
typedef struct batConfig
{
    uint32_t startAt;
    uint32_t endAt;
    float    sumMa;
    int     currentDischargeMa;
    int     targetDischargeMa;
    int     minimumVoltage;
};
/**

*/
class batScreen
{
public:
        batScreen(   batConfig *c,Adafruit_ILI9341_STM *tft)
        {
            _config=c;
            _tft=tft;
        } 
        virtual ~batScreen()
        {
            _config=NULL;
            _tft=NULL;
        }
        virtual void      draw()=0;
        virtual batScreen *process(int mV,int mA,int currentTime,int leftRight,bool pressed)=0; // return NULL if the current screen stays the same
protected:
                void prettyPrint(int val,int x,int y,const char *unit);
protected:
        batConfig *_config;
        Adafruit_ILI9341_STM *_tft;
};

// EOF
