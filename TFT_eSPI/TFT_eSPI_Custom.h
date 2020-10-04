        ////////////////////////////////////////////////////
        //       TFT_eSPI generic driver functions        //
        ////////////////////////////////////////////////////

// This is a generic driver for Arduino boards, it supports SPI interface displays
// 8 bit parallel interface to TFT is not supported for generic processors

#pragma once

// Processor ID reported by getSetup()
#define PROCESSOR_ID 0x0000

// Include processor specific header
// None

// Processor specific code used by SPI bus transaction startWrite and endWrite functions
#define SET_BUS_WRITE_MODE // Not used
#define SET_BUS_READ_MODE  // Not used

// Code to check if DMA is busy, used by SPI bus transaction startWrite and endWrite functions
#define DMA_BUSY_CHECK // Not used so leave blank

// To be safe, SUPPORT_TRANSACTIONS is assumed mandatory
#if !defined (SUPPORT_TRANSACTIONS)
  #define SUPPORT_TRANSACTIONS
#endif

// Initialise processor specific SPI functions, used by init()
#define INIT_TFT_DATA_BUS

// If smooth fonts are enabled the filing system may need to be loaded
#ifdef SMOOTH_FONT
  // Call up the filing system for the anti-aliased fonts
  //#define FS_NO_GLOBALS
  //#include <FS.h>
#endif

  #define DC_C digitalWrite(TFT_DC, LOW)
  #define DC_D digitalWrite(TFT_DC, HIGH)
  #define CS_L digitalWrite(TFT_CS, LOW)
  #define CS_H digitalWrite(TFT_CS, HIGH)

////////////////////////////////////////////////////////////////////////////////////////
// Make sure TFT_RD is defined if not used to avoid an error message
////////////////////////////////////////////////////////////////////////////////////////
#ifndef TFT_RD
  #define TFT_RD -1
#endif

////////////////////////////////////////////////////////////////////////////////////////
// Define the WR (TFT Write) pin drive code
////////////////////////////////////////////////////////////////////////////////////////
#ifdef TFT_WR
  #define WR_L digitalWrite(TFT_WR, LOW)
  #define WR_H digitalWrite(TFT_WR, HIGH)
#endif

////////////////////////////////////////////////////////////////////////////////////////
// Define the touch screen chip select pin drive code
////////////////////////////////////////////////////////////////////////////////////////
#if !defined TOUCH_CS || (TOUCH_CS < 0)
  #define T_CS_L // No macro allocated so it generates no code
  #define T_CS_H // No macro allocated so it generates no code
#else
  #define T_CS_L digitalWrite(TOUCH_CS, LOW)
  #define T_CS_H digitalWrite(TOUCH_CS, HIGH)
#endif

////////////////////////////////////////////////////////////////////////////////////////
// Make sure TFT_MISO is defined if not used to avoid an error message
////////////////////////////////////////////////////////////////////////////////////////
#ifndef TFT_MISO
  #define TFT_MISO -1
#endif


      #define tft_Write_8(C)   spi.transfer(C)
      #define tft_Write_16(C)  spi.transfer16(C)
      #define tft_Write_16S(C) spi.transfer16(((C)>>8) | ((C)<<8))

  #define tft_Write_32(C) \
  tft_Write_16((uint16_t) ((C)>>16)); \
  tft_Write_16((uint16_t) ((C)>>0))

  #define tft_Write_32C(C,D) \
  tft_Write_16((uint16_t) (C)); \
  tft_Write_16((uint16_t) (D))

  #define tft_Write_32D(C) \
  tft_Write_16((uint16_t) (C)); \
  tft_Write_16((uint16_t) (C))

////////////////////////////////////////////////////////////////////////////////////////
// Macros to read from display using SPI or software SPI
////////////////////////////////////////////////////////////////////////////////////////
#if defined (TFT_SDA_READ)
  // Use a bit banged function call for STM32 and bi-directional SDA pin
  #define TFT_eSPI_ENABLE_8_BIT_READ // Enable tft_Read_8(void);
  #define SCLK_L digitalWrite(TFT_SCLK, LOW)
  #define SCLK_H digitalWrite(TFT_SCLK, LOW)
#else
  // Use a SPI read transfer
  #define tft_Read_8() spi.transfer(0)
#endif

// EOF