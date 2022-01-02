/***************************************************
 Battery Tester
 * GPL v2
 * (c) mean 2018 fixounet@free.fr
 ****************************************************/


#include "push_button.h"
#include "screenBase.h"
#include "screenIdle.h"
#include "screenDischarging.h"
#include "gfxfont.h"
#include "xpt2046.h"
#include "dso_eeprom.h"
#include "batterySensor.h"
#include "lnSPI.h"
#include "gd32_spi.h"
#include "adc_engine.h"

extern const GFXfont FreeSans24pt7b ;
extern const GFXfont FreeSans18pt7b ;
extern const GFXfont FreeSans9pt7b ;

//extern void touchCalibration(XPT2046 *xpt, TFT_eSPI *tft);

#include "myPinout.h"
//#define TEST_DIS 

//
// Our globals

batConfig            config=
{
  {
    100,  //int     resistor1000; // 1000x the wiring resistor
    500,  //int     initialDischargeMa;
    3000  //int     minimumVoltage;  
  },
  0, // duration
  0, // sumMa
  0, // targetDischargeMa
  0, // currentDisc
  NULL, // screen
  NULL, // MCP
  NULL, // rotary
  NULL, // INA
  0,    // batteyResistance 

};
#if 0
#define BootSequence(x,y) {Logger(x);  tft->setCursor(10, y*2);       tft->myDrawString(x);xDelay(10);}
#else
#define BootSequence(x,y) {Logger(x); ;xDelay(10);}
#endif
/*
 */
void myLoop(void) ;
/**
 * 
 */
class MainTask : public xTask//,XPT2046Hook
{
public:
            MainTask() : xTask("MainTask",10,800)
            {
              screen=NULL;
              currentScreen=NULL;
            }
            virtual void pressEvent(int x,int y)
            {
                
            }
            void    run(void);
            void    initTft();
            void    loop(void) ;
protected:
            
            ili9341              *screen;
            batScreen            *currentScreen;         
            int                  gateVoltage=0;    
            xMutex               *spiMutex;
            CurrentState         currentState;
            BatterySensor        *batSensor;
            hwlnSPIClass         *spi;
            //   XPT2046              *xpt2046=NULL;

};


/**
 * 
 */
void MainTask::initTft()
{
  
    spiMutex=new xMutex();
    spi=new hwlnSPIClass(0,-1);
    
    spi->setBitOrder(SPI_MSBFIRST);
    spi->setSpeed(10*1000*1000);
    spi->begin();

    screen=new lnSpi9341(240,320,spi,   TFT_DC, TFT_CS, TFT_RST);
    screen->init();
    screen->setRotation(1);
    screen->fillScreen(0);
    screen->setFontFamily( &FreeSans9pt7b, &FreeSans18pt7b, &FreeSans24pt7b) ;
    screen->setFontSize(ili9341::MediumFont);
    screen->setTextColor(0xffff,0);
}
/**
 * 
 */

void engineCb(void *cookie, lnPin p, int value)
{
  Logger("Pin:%x Value=%d\n",p,value);
}

void setup() 
{
  // Shutdown ref
  lnPinMode(PWM_PIN,lnPWM);  
  digitalWrite(PWM_PIN,0);
  MainTask *mainTask=new MainTask();
  mainTask->start();

 

}
/**
 * 
 */
void    MainTask::run(void)
{  

#if 1  
  initTft();   
  screen->print(100,100,"Hello there !");
  screen->square(0x1f,40,40,100,100);
  screen->square(0x3f<<5,80,120,100,100);
#endif

  adcEngine *engine=new adcEngine;
  engine->add(PA1,engineCb,NULL);
  engine->add(PA2,engineCb,NULL);
  engine->start();

#if 0
  
  xpt2046=new XPT2046(SPI,TOUCH_CS,TOUCH_IRQ,2400*1000,spiMutex); // 2.4Mbits
  if(! DSOEeprom::read())
  {
        touchCalibration(xpt2046,tft);
        DSOEeprom::read();
  }
  
 
  
  // reconfigure gate as pwm
 int scaler, ovf,cmp;

  pinMode(PWM_PIN,PWM);  
  pwmWrite(PWM_PIN,0);
  myPwm(PWM_PIN,PWM_FQ);
  pwmGetScaleOverFlowCompare(PWM_FQ,scaler,ovf,cmp);
  pwmFromScalerAndOverflow(PWM_PIN,scaler,ovf);
  pwmRestart(PWM_PIN);
  pwmSetRatio(PWM_PIN, 0);
 
  config.tft=tft;
  
  batSensor=new BatterySensor(ADC_VOLT_PIN,ADC_CURRENT_PIN);
  
  xpt2046->setup((int *)DSOEeprom::calibration);
  xpt2046->setHooks(NULL);
  xpt2046->start();
  
  
  float current,voltage;
  char st[60];
  while(1)
  {
        batSensor->getVoltageCurrent(voltage,current);        
        tft->setCursor(10,160);
        sprintf(st,"V:%2.2f, A:%2.2f\n",voltage,current);        
        tft->myDrawString(st);        
        xDelay(300);
    }

  while(1)
    {
        xDelay(10);
    }    
  
#ifdef TEST_DIS
  currentScreen=new dischargingScreen(   &config,4000);
#else  
  currentScreen =new idleScreen(&config);
#endif    
  currentScreen->draw();
  
 #if 0 
  ina219->autoZero();
  ina219->setMultiSampling(2);   
#endif
  config.userSettings.loadSettings();
#endif
  while(1)
  {
        xDelay(100);
  }  
  
}
/**
 * 
 */
void MainTask::loop(void) 
{
    // Returns NULL if we stay on the same screen
    // the new screen otherwise
    batScreen *s=currentScreen->process();
    if(s)
    {
        delete currentScreen;
        currentScreen=s;
        s->draw();
        
        // Purge pending events if any
    }
    xDelay(50);
}
/**
 * 
 */
void loop()
{
    xDelay(1000);
}
//--EOF
