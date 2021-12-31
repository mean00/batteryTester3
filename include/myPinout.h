#pragma once


//#define TEST_DIS 

// ILI9341 is using HW SPI + those pins
#define TFT_DC          PB14
#define TFT_RST         PB13
#define TFT_CS          PB12

#define INA219_I2C_ADR  0x40
#define MCP7245_I2C_ADR 0x60

// TOUCH SCREEN
#define TOUCH_CS        PB5
#define TOUCH_IRQ       PB4

// Voltage & current Sense
#define ADC_VOLT_PIN    PA3
#define ADC_CURRENT_PIN PA4

// Battery connect / Disconnect
#define BAT_CONNECT     PB10

// Current regulation (PWM) pin
#define PWM_PIN         PB0
#define PWM_FQ  (20*1000)
