/***************************************************
 Battery Tester
 * GPL v2
 * (c) mean 2018 fixounet@free.fr
 ****************************************************/

#include <Wire.h>
#include "SPI.h"
#include "wav_irotary.h"
#include "push_button.h"
#include "screenBase.h"
#include "screenIdle.h"
#include "screenDischarging.h"
#include "dso_debug.h"
#include "RotaryEncoder/wav_irotary.h"
#include "xpt2046.h"
#include "dso_eeprom.h"
#include "batterySensor.h"
#include "myPwm.h"

extern const GFXfont FreeSans24pt7b ;
extern const GFXfont FreeSans18pt7b ;
extern const GFXfont FreeSans9pt7b ;

extern void touchCalibration(XPT2046 *xpt, TFT_eSPI *tft);

#include "myPinout.h"
//#define TEST_DIS 


//
// Our globals

batConfig            config=
{
    200,      // Wire resistor, computed automatically
    0,      //int     currentDischargeMa;
    3000,   //     minimumVoltage;
    
    0,      //uint32_t duration;
    0,      // float    sumMa;
    
#ifdef TEST_DIS    
    200,
#else
    500,    // int     targetDischargeMa;
#endif
    
    NULL,   // TFT
    NULL    
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
class MainTask : public xTask,XPT2046Hook
{
public:
            MainTask() : xTask("MainTask",10,400)
            {

            }
            virtual void pressEvent(int x,int y)
            {
                
            }
            void    run(void);
            void    initTft();
            void    loop(void) ;
protected:
            TFT_eSPI             *tft=NULL;
            WavRotary            *rotary=NULL;
            batScreen            *currentScreen=NULL;
            XPT2046              *xpt2046=NULL;
            int                  gateVoltage=0;    
            xMutex               *spiMutex;
            CurrentState         currentState;
            BatterySensor        *batSensor;
};


/**
 * 
 */
void MainTask::initTft()
{
    if(tft)
    {
        delete tft;    
        tft=NULL;
    }
    // Deep reset of screen
    pinMode(TFT_RST,OUTPUT);
    digitalWrite(TFT_RST,LOW);
    delay(100);  
    digitalWrite(TFT_RST,HIGH);
    spiMutex=new xMutex();

    tft = new TFT_eSPI_stm32duino(SPI,spiMutex,240,320,TFT_CS,TFT_DC,TFT_RST);
    
    tft->init();  
    tft->setRotation(3);
    tft->fillScreen(ILI9341_BLACK);
        
    tft->setFontFamily(&FreeSans9pt7b,&FreeSans18pt7b,&FreeSans24pt7b);
    tft->setFontSize(TFT_eSPI::MediumFont);
}
/**
 * 
 */
void mySetup() 
{
  // switch to uart ASAP    
  Serial.end();
  Serial1.begin(115200);  //Wire.begin();
  Serial.end();
  Serial1.begin(115200);  
    
  Logger("Init"); 
  
  SPI.begin();
  SPI.setBitOrder(MSBFIRST); // Set the SPI bit order
  SPI.setDataMode(SPI_MODE0); //Set the  SPI data mode 0
//  SPI.setClockDivider (SPI_CLOCK_DIV4); // Given for 10 Mhz...
  SPI.setClockDivider (SPI_CLOCK_DIV8); // Given for 10 Mhz...
    
  // Shutdown ref
  pinMode(PWM_PIN,OUTPUT);  
  digitalWrite(PWM_PIN,0);

  
  // Start freeRTOS
  MainTask *mainTask=new MainTask();
  vTaskStartScheduler();        
}
/**
 * 
 */
void    MainTask::run(void)
{  
  Wire.setClock(100*1000);
  Wire.begin();
    
  initTft();   
  tft->fillScreen(ILI9341_BLACK);
  tft->myDrawString("Hello there !");

  
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
  
  while(1)
  {
        loop();
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
        rotary->readEvent();
        rotary->getCount();        
    }
    xDelay(50);
}
/**
 * 
 */
void myLoop()
{
    
}
//--EOF
