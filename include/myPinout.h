#pragma once


//#define TEST_DIS 

// ILI9341 is using HW SPI + those pins
#define TFT_DC          PB14
#define TFT_RST         PB13
#define TFT_CS          PB12


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
#define PWM_FQ          (20*1000)

#define BUTTON_RIGHT    PB8 // 45        
#define BUTTON_DOWN     PB9 // 46
#define BUTTON_OK       PB6 // 42
#define BUTTON_UP       PB7 // 43
#define BUTTON_LEFT     PB1 // 19
// GND

