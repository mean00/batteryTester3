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

// ILI9341 is using HW SPI + those pins
#define TFT_DC          PB0
#define TFT_RST         PB11
#define TFT_CS          PB10

#define INA219_I2C_ADR  0x40
#define MCP7245_I2C_ADR 0x60
#define DISABLE_INA219

//
// Our globals
Adafruit_ILI9341_STM *tft=NULL;
WavRotary            *rotary=NULL;
simpler_INA219       *ina219=NULL;
Adafruit_MCP4725     *mcp4725=NULL;

int                 gateVoltage=0;

#define BootSequence(x,y) {Serial.println(x);  tft->setCursor(10, y*2);       tft->println(x);delay(10);}

/*
 */
void mySetup() 
{
  Serial.begin(115200);
//  delay(5000);
  Serial.println("Init"); 
 
 
  
  SPI.begin();
  SPI.setBitOrder(MSBFIRST); // Set the SPI bit order
  SPI.setDataMode(SPI_MODE0); //Set the  SPI data mode 0
  SPI.setClockDivider (SPI_CLOCK_DIV2);
  
  Serial.println("TFT"); 
  
  tft = new Adafruit_ILI9341_STM(TFT_CS, TFT_DC,TFT_RST);
  tft->begin();  
  tft->fillScreen(ILI9341_BLACK);
  tft->setTextColor(ILI9341_WHITE);  
  tft->setRotation(1);
  tft->setTextSize(3);    
  
   //Wire.begin();
  BootSequence("MCP4725",30);
  mcp4725=new Adafruit_MCP4725();
  mcp4725->begin(MCP7245_I2C_ADR);
  mcp4725->setVoltage(0,false); 
  
  
  
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
  
  tft->fillScreen(ILI9341_BLACK);
}

/**
 */
void myLoop(void) 
{
    
    int count=rotary->getCount();
    if(count)
    {
        gateVoltage+=40*count;
        if(gateVoltage>4090) gateVoltage=4090;
        if(gateVoltage<0) gateVoltage=0;
        mcp4725->setVoltage(gateVoltage,false); 
        
        
    }
    
            
    tft->fillScreen(ILI9341_BLACK);    
    tft->setCursor(10, 10);    
    tft->println(gateVoltage);
    
    
    float actual=(gateVoltage *3300)/4096.;
    tft->setCursor(10, 120);    
    tft->println((int)actual);
    
    
    delay(100);
     Serial.println("*"); 
#ifndef DISABLE_INA219  
    float voltage=ina219->getBusVoltage_V();
    tft->setCursor(10, 50);   
    tft->println(voltage);
//
    int current=ina219->getCurrent_mA();
    tft->setCursor(10, 80);   
    tft->println(current);
#endif
}
//--