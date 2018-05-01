/***************************************************
  This is our GFX example for the Adafruit ILI9341 Breakout and Shield
  ----> http://www.adafruit.com/products/1651

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include "SPI.h"
#include "Adafruit_GFX_AS.h"
#include "Adafruit_ILI9341_STM.h"
#include "Rotary.h"
#include "wav_irotary.h"

// For the Adafruit shield, these are the default.
#define TFT_DC PB0
#define TFT_RST PB11
#define TFT_CS PB10
//
// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341_STM *tft=NULL;
WavRotary            *rotary=NULL;
// If using the breakout, change pins as desired
//Adafruit_ILI9341_STM tft = Adafruit_ILI9341_STM(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);
//Adafruit_ILI9341_STM tft = Adafruit_ILI9341_STM(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

void setup() 
{
  Serial.begin(9600);
  Serial.println("Rotary Test!"); 
 
  SPI.begin();
  SPI.setBitOrder(MSBFIRST); // Set the SPI bit order
  SPI.setDataMode(SPI_MODE0); //Set the  SPI data mode 0
  SPI.setClockDivider (SPI_CLOCK_DIV2);

  tft = new Adafruit_ILI9341_STM(TFT_CS, TFT_DC);
  tft->begin();  
  tft->fillScreen(ILI9341_BLACK);
  tft->setTextColor(ILI9341_WHITE);  
  tft->setTextSize(4);    
  rotary=new WavRotary(PA1,PA2);
}

static int counter=0;
void loop(void) 
{
    int count=rotary->getCount();
    if(count)
    {
        counter+=count;
        tft->fillScreen(ILI9341_BLACK);    
        tft->setCursor(10, 10);    
        tft->println(counter);
    }
    delay(100);
}
