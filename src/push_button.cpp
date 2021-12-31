/***************************************************
 Battery Tester
 * GPL v2
 * (c) mean 2018 fixounet@free.fr
 * 
 * Debounce done in hardware with a Rc filter !
 ****************************************************/


#include <Wire.h>
#include "push_button.h"
static PushButton *current=NULL;
 /**
  */
 
static void myInterrupt()
{
  if(!current) return;
  current->interrupt();
}
#define SETPIN(x) {    pinMode(x,INPUT_PULLUP);    attachInterrupt(x, myInterrupt, FALLING); }



/**
 */
 PushButton::PushButton(int pin)
 {
    current=this;
    _pressed=false;
    noInterrupts(); 
    SETPIN(pin);
    interrupts();
 }
 /**
  */
 bool          PushButton::pressed()
 {
     noInterrupts();
     bool c=_pressed;
     _pressed=false;
     interrupts();
     return c;
 }
 
 /**
  */
 void PushButton::interrupt()
 {
    _pressed=true;
 }

 // EOF
