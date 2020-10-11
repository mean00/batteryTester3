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
#include "dso_eeprom.h"

/*
 */
uint8_t ucHeap[ configTOTAL_HEAP_SIZE ];
//--EOF
