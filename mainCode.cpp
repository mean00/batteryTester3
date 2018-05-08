/***************************************************
 Battery Tester
 * GPL v2
 * (c) mean 2018 fixounet@free.fr
 ****************************************************/

#include <Wire.h>
#include "SPI.h"
#include "Adafruit_GFX_AS.h"
#include "Adafruit_ILI9341_STM.h"
#include "Rotary.h"
#include "wav_irotary.h"
#include "simpler_INA219.h"
#include "Adafruit_MCP4725.h"
#include "push_button.h"
#include "screenBase.h"
#include "screenIdle.h"

// ILI9341 is using HW SPI + those pins
#define TFT_DC          PB0
#define TFT_RST         PB1
#define TFT_CS          PB10

#define INA219_I2C_ADR  0x40
#define MCP7245_I2C_ADR 0x60
//#define DISABLE_INA219

//
// Our globals
Adafruit_ILI9341_STM *tft=NULL;
WavRotary            *rotary=NULL;
simpler_INA219       *ina219=NULL;
Adafruit_MCP4725     *mcp4725=NULL;
PushButton           *pushButton=NULL;
batScreen            *currentScreen=NULL;

int                 gateVoltage=0;
batConfig           config={
    0, //uint32_t startAt;
    0, //uint32_t endAt;
    0, // float    sumMa;
    0, //int     currentDischargeMa;
    500, // int     targetDischargeMa;
    3000 //     minimumVoltage;
};
#if 1
#define BootSequence(x,y) {Serial.println(x);  tft->setCursor(10, y*2);       tft->println(x);delay(10);}
#else
#define BootSequence(x,y) {Serial.println(x); ;delay(10);}
#endif
/*
 */

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

    tft = new Adafruit_ILI9341_STM(TFT_CS, TFT_DC,TFT_RST);
    tft->begin();  
    tft->fillScreen(ILI9341_BLACK);
    tft->setTextColor(ILI9341_WHITE,ILI9341_BLACK);  
    tft->setRotation(3);
    tft->setTextSize(3);   
}

void mySetup() 
{
  Serial.println("Init"); 
  
  SPI.begin();
  SPI.setBitOrder(MSBFIRST); // Set the SPI bit order
  SPI.setDataMode(SPI_MODE0); //Set the  SPI data mode 0
  SPI.setClockDivider (SPI_CLOCK_DIV4); // Given for 10 Mhz...
  
  delay(100);
  
  Serial.println("TFT"); 
  initTft();   
  
   //Wire.begin();
  BootSequence("MCP4725",30);
  mcp4725=new Adafruit_MCP4725();
  mcp4725->begin(MCP7245_I2C_ADR);
  mcp4725->setVoltage(0,false); 
  
  pushButton=new PushButton(PA0);
  
  BootSequence("Rotary",10);
  Serial.println("Rotary"); 
  rotary=new WavRotary(PA2,PA1);
#ifndef DISABLE_INA219  
  BootSequence("Ina219",20);
  ina219=new simpler_INA219(); //INA219_I2C_ADR,100); // 100 mOhm
#endif  
  
#ifndef DISABLE_INA219  
  BootSequence("Zero",40);
  delay(10); // no current, we can autocalibrate the ina
  //ina219->autoZero();
#endif

  BootSequence("All ok",50);
  //initTft();
  tft->fillScreen(ILI9341_BLACK);
  
  currentScreen =new idleScreen(&config,tft);
}

/**
 */
void myLoop(void) 
{
    static int currentTime=0;
    int count=rotary->getCount();
    bool pressed=pushButton->pressed();
    float voltage=ina219->getBusVoltage_V();
    int current=ina219->getCurrent_mA();
    
    
    batScreen *s=currentScreen->process(voltage*1000.,current,currentTime,count,pressed); //s(int mV,int mA,int currentTime,int leftRight,bool pressed)=0;
    // switch to new screen
    if(s)
    {
        delete currentScreen;
        currentScreen=s;
        s->draw();
    }

    delay(10);
    Serial.println("*"); 
}
//--