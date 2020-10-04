/***************************************************
 Battery Tester
 * GPL v2
 * (c) mean 2018 fixounet@free.fr
 ****************************************************/

#include <Wire.h>
#include "SPI.h"
#include "wav_irotary.h"
#include "simpler_INA219.h"
#include "simplerMCP4725.h"
#include "push_button.h"
#include "screenBase.h"
#include "screenIdle.h"
#include "screenDischarging.h"
#include "dso_debug.h"
#include "RotaryEncoder/wav_irotary.h"
#include "xpt2046.h"

extern const GFXfont FreeSans24pt7b ;
extern const GFXfont FreeSans18pt7b ;
extern const GFXfont FreeSans9pt7b ;

xMutex  *spiMutex;


//#define TEST_DIS 

// ILI9341 is using HW SPI + those pins
#define TFT_DC          PB0
#define TFT_RST         PB1
#define TFT_CS          PB10

#define INA219_I2C_ADR  0x40
#define MCP7245_I2C_ADR 0x60

// TOUCH SCREEN
#define TOUCH_CS        PB8
#define TOUCH_IRQ       PB11

//
// Our globals

TFT_eSPI_extended    *tft=NULL;
WavRotary            *rotary=NULL;
simpler_INA219       *ina219=NULL;
myMCP4725            *mcp4725=NULL;
batScreen            *currentScreen=NULL;
XPT2046              *xpt2046=NULL;
int                  gateVoltage=0;
batConfig            config=
{
    0, // Wire resistor, computed automatically
    0, //uint32_t duration;
    0, // float    sumMa;
    0, //int     currentDischargeMa;
#ifdef TEST_DIS    
    200,
#else
    500, // int     targetDischargeMa;
#endif
    3000, //     minimumVoltage;
    50,   // Battery drop when going to 500mA
    NULL,  // TFT
    NULL    
};
#if 0
#define BootSequence(x,y) {Logger(x);  tft->setCursor(10, y*2);       tft->println(x);xDelay(10);}
#else
#define BootSequence(x,y) {Logger(x); ;xDelay(10);}
#endif
/*
 */
uint8_t ucHeap[ configTOTAL_HEAP_SIZE ];
void myLoop(void) ;
/**
 * 
 */
class MainTask : public xTask
{
public:
            MainTask() : xTask("MainTask",10,400)
            {

            }
            void    run(void);
protected:
};


void initTft()
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

    tft = new TFT_eSPI_extended(spiMutex);
    
    tft->init();  
    tft->setRotation(3);
    tft->fillScreen(ILI9341_BLACK);
    
    
    tft->setFontFamily(&FreeSans9pt7b,&FreeSans18pt7b,&FreeSans24pt7b);
    tft->setFontSize(TFT_eSPI_extended::MediumFont);
    
    
}
/**
 * 
 */
void touchIRQ()
{
    
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
  
  delay(100);
  
  Logger("TFT"); 
  initTft();   
  
  xpt2046=new XPT2046(SPI,TOUCH_CS,TOUCH_IRQ,2*1000*1000,spiMutex); // 2Mbits
  xpt2046->start();
  
  
  
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
  
  BootSequence("MCP4725",30);
  mcp4725=new myMCP4725(Wire,MCP7245_I2C_ADR);
  mcp4725->setVoltage(0); 
  config.mcp=mcp4725;
  config.tft=tft;
  
  
  BootSequence("Rotary",10);
  rotary=new WavRotary(PA2,PA1,PA0);
  rotary->start();
#ifndef DISABLE_INA219  
  BootSequence("Ina219",20);
  ina219=new simpler_INA219(); //INA219_I2C_ADR,100); // 100 mOhm
#endif  
  
#ifndef DISABLE_INA219  
  BootSequence("Zero",40);
  delay(10); // no current, we can autocalibrate the ina
  //ina219->autoZero();
#endif
#if 1
  BootSequence("All ok",50);
  initTft();  
  tft->fillScreen(ILI9341_BLACK);

  
#ifdef TEST_DIS
  currentScreen=new dischargingScreen(   &config,4000);
#else  
  currentScreen =new idleScreen(&config);
#endif    
  currentScreen->draw();
  
  pinMode(TOUCH_IRQ,INPUT_PULLDOWN);
  attachInterrupt(TOUCH_IRQ, touchIRQ,FALLING);
#endif  
  while(1)
  {
    xpt2046->run();
    xDelay(800);
  }
  
  while(1)
    {
        myLoop();
    }  
}

/**
 */
void myLoop(void) 
{
    static int currentTime=0;
    float voltage=ina219->getBusVoltage_V();
    int current=ina219->getCurrent_mA();    
    int evt=rotary->readEvent();
    
    bool pressed=false;
    int count=0;
    
    if(evt & WavRotary::ROTARY_CHANGE)
    {
        count=rotary->getCount();
    }
    if(evt & WavRotary::SHORT_PRESS)
    {
        pressed=true;
    }

    batScreen *s=currentScreen->process(voltage*1000.,current,currentTime,count,pressed); //s(int mV,int mA,int currentTime,int leftRight,bool pressed)=0;
    // switch to new screen
    if(s)
    {
        delete currentScreen;
        currentScreen=s;
        s->draw();
    }
    xDelay(50);
}
//--
