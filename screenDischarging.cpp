/***************************************************
 * Battery Tester
 * GPL v2
 * (c) mean 2018 fixounet@free.fr
 ****************************************************/

#include "screenInclude.h"
#include "screenDischarging.h"
#include "screenError.h"
#include "voltage.h"
#include "simplerMCP4725.h"
#include "wav_irotary.h"

#define CURRENT_ERROR_MARGIN   2 // Error margin in mA
#define REFRESH_PERIOD_IN_SEC 5 // Refresh mA count every x sec

#define DEBUG

/**
 * 
 * @param c
 * @param currentMv
 */
batScreen *dischargingScreen::goToEnd(EndOfChargeCause c)
{
    int mn,s;
    timer.wallClock(mn,s);
    float duration=s+mn*60;
    _config->duration=(int)((duration+29.)/60.);
    return new finishedScreen(_config,c);
}
/**
 * \fn updateTargetCurrent
 * \brief Set the gate to have the target current but do not exceed the max power dissipation
 * That's why we need the voltage
 * @param currentMv
 */
void dischargingScreen::updateTargetCurrent()
{
    resetAverage();
    evaluateTargetAmp();
    gateCommand=computeGateCommand(_config->currentDischargeMa);
    originalGateCommand=gateCommand;
    _config->mcp->setVoltage(gateCommand);
    resyncing=3; // wait a bit for stuff to stabilize
}

/**

*/
dischargingScreen::dischargingScreen(   batConfig *c,int currentMv) : batScreen(c),timer(REFRESH_PERIOD_IN_SEC),smallTimer(AVERAGING_SAMPLE_PERIOD,1),debounceTimer(100,1)
{
    _config->sumMa=0;
    _config->targetDischargeMa=_config->userSettings.initialDischargeMa;
    paused=false;    
    updateTargetCurrent();
    resyncing=0;
    range=RANGE_HIGH;
    resetAverage();
    
}

/**
 * \fn computeAverage
 * \brief average voltage and current to avoid glitches (bump into the desk for example)
 * @param mV
 * @param mA
 * @param avgV
 * @param avgA
 * @return 
 */
bool dischargingScreen::computeAverage(int mV,int mA,int &avgV, int &avgA)
{
    if(-1==sampleIndex) // first sample
    {
        for(int i=0;i<AVERAGING_SAMPLE_COUNT;i++)
        {
            samplema[i]=mA;
            samplemv[i]=mV;
        }
        sampleIndex=0;
    }
    samplema[sampleIndex]=mA;
    samplemv[sampleIndex]=mV;
    sampleIndex=(sampleIndex+1)%AVERAGING_SAMPLE_COUNT;
        
    
    avgA=0;
    avgV=0;
    for(int i=0;i<AVERAGING_SAMPLE_COUNT;i++)
        {
            avgA+=samplema[i];
            avgV+=samplemv[i];
        }
    avgA/=AVERAGING_SAMPLE_COUNT;
    avgV/=AVERAGING_SAMPLE_COUNT;
    return true;
}

/**
 * \fn resetAverage
 * \brief purge history
 * @param mv
 * @param mA
 * @return 
 */
bool dischargingScreen::resetAverage()
{
        sampleIndex=-1;
        return true;
}

/**
 * \fn adjustGateVoltage
 * \brief allow small tuning to gate command to compensate for the approximation given by formula
 * @param avgA
 * @param avgV
 * @return 
 */
bool dischargingScreen::adjustGateVoltage(int avgV,int avgA)
{
    // correct gate if needed
    int inc=0;
    int tooLow=_config->currentDischargeMa-CURRENT_ERROR_MARGIN;
    int tooHigh=_config->currentDischargeMa+CURRENT_ERROR_MARGIN;
    if(avgA < tooLow)  inc=1;
    if(avgA > tooHigh) inc=-1;
    if(!inc) return false; // nothing to do
    
    float er=100.*fabs(gateCommand-originalGateCommand);
    er=er/(float)originalGateCommand;
    if( er>5. ) // Dont exceed 5%
        return false;    
    gateCommand+=inc;
    _config->mcp->setVoltage(gateCommand);
    return true;
}
/**
 * 
 * @param leftRight
 * @return 
 */
bool dischargingScreen::LeftOrRigh(int leftRight)
{
     // Increase/Decrease current
    if(leftRight)
    {
        int a=_config->targetDischargeMa;
        if(a<1500 && leftRight>0) a+=100;
        if(a>150 && leftRight<0) a-=100;
        if(a!=_config->targetDischargeMa)
        {
            _config->targetDischargeMa=a;
            updateTargetCurrent();
            updateInfo();
            draw();
        }
    }
    return true;
}
/**
 * 
 * @return 
 */
bool dischargingScreen::processEvents()
{
    bool pressed=false;;
    int leftRight=0;

    
    
    WavRotary::EVENTS evt=_config->rotary->readEvent();
    if(evt & WavRotary::SHORT_PRESS)
        pressed=true;
    if(evt & WavRotary::ROTARY_CHANGE)
        leftRight=_config->rotary->getCount();

     if(!pressed && !leftRight)
         return false; // nothing to do

    // toggle on /off pause mode
    if(pressed)
    {
        if(debounceTimer.elapsedMS()>=200) // xx ms debounce
        {
            paused=!paused;
            if(paused)
            {
              // stop gate
              _config->mcp->setVoltage(0);              
            }else
            { // Re-enable gate
              updateTargetCurrent();
              xDelay(10);
            }
            debounceTimer.reset();
            draw();
        }
    }
    if(leftRight)
    {
       LeftOrRigh(leftRight);
    }   
    return true;
}

/**
 * 
 * @return 
 */
batScreen *dischargingScreen::process()
{
    CurrentState s;
    readState(s);
    int mV=s.mVoltage;
    int mA=s.mCurrent;

    // Wait for things to be taken into account
    if(resyncing)
    {
        xDelay(50);
        resyncing--;
        return NULL;
    }

    
    
    processEvents();
  
    if(paused)
    {
        drawVoltageAndCurrent(s);
        return NULL;
    }

    
    // dont hammer the loop
    if(!smallTimer.elapsed())
    {
        xDelay(10); // dont busy loop
        return NULL;
    }
    smallTimer.nextPeriod(); // evert 100 ms we go here
    
    int avgA,avgV;
    computeAverage(mV,mA,avgV,avgA);
    // and take wiring into account
    float vDrop=(float)avgA*(float)_config->userSettings.resistor1000;
    vDrop/=1000.; // Ohm->milliOhm
    avgV=avgV+vDrop;    
   
   
    // Small adjustment to gate command
    CurrentState tmp;
    tmp.mCurrent=avgA;
    tmp.mVoltage=avgV;
    drawVoltageAndCurrent(tmp);    
   // adjustGateVoltage(avgV,avgA);
    
   
    // At high current, the voltage is unreliable due to parasitic resistance
    // so as soon as the voltage goes "close" to 3V, we cap the current
    // so that the actual battery voltage becomes a more reliable reading
    // We keep margin so that it is safe-ish
    switch(range)
    {
        case RANGE_HIGH:
                        int limit;
                        if(_config->currentDischargeMa>700)
                            limit=3100;
                        else
                            limit=3300;
                        if(avgV<limit)
                            if(_config->currentDischargeMa > 500)
                                {
                                    _config->targetDischargeMa = 500; // drop to 400 mA
                                    updateTargetCurrent();
                                    range=RANGE_MED;
                                    resyncing=3;
                                    return NULL;
                                }
                        break;
        case RANGE_MED:
                        if(avgV<3200)
                            if(_config->currentDischargeMa > 250)
                                {
                                    _config->targetDischargeMa = 250; // drop to 400 mA
                                    updateTargetCurrent();
                                    range=RANGE_LOW;
                                    resyncing=3;
                                    return NULL;
                                }
                        break;
        case RANGE_LOW:                        
        default:
            break;
        
    }
   
   
    
    
    if(avgV<_config->userSettings.minimumVoltage)
    {
        return goToEnd(END_VOLTAGE_LOW);
    }
    if(mA > BAT_MAX_CURRENT)
    {
        return goToEnd(END_CURRENT_HIGH);
    }
    
    
    
    if(!timer.rdv()) return NULL;
    // update sumA
    _config->sumMa+=REFRESH_PERIOD_IN_SEC*avgA;
    timer.nextPeriod();   
    updateInfo();
    return NULL;
    
}
/**
 * \fn updateInfo
 * \brief Redraw screen, lightweight version
 */
void dischargingScreen::updateInfo()
{
    int mn,sec,h;
    char buffer[200];
    
     
    timer.wallClock(mn,sec);
    _tft->setTextColor(ILI9341_WHITE,ILI9341_BLACK);          
    
    float c=_config->sumMa;
    c/=3600.;
    
    sprintf(buffer,"%04d mA/h ",(int)c); // 10 sec -> hour
    _tft->setFontSize(TFT_eSPI_extended::BigFont);
    _tft->setCursor(18, 60);       
    _tft->myDrawString(buffer);
    
    h=mn/60;
    mn-=h*60;
    _tft->setFontSize(TFT_eSPI_extended::MediumFont);
    sprintf(buffer,"%02d:%02d:%02d",h,mn,sec);
    _tft->setCursor(18, 120);       
    _tft->myDrawString(buffer);
}

/**
 * \fn draw
 * \brief complete redraw of background
 */
void dischargingScreen::draw()
{   
    char buffer[50];    
    if(!paused)
    {
        setTitle(ILI9341_BLACK,ILI9341_WHITE,4, "     DISCHARGING         ");
    }else
    {
        setTitle(ILI9341_RED,ILI9341_WHITE,4, "         PAUSED        ");
    }
    _tft->setTextColor(ILI9341_WHITE,ILI9341_BLACK);  
    updateInfo();
#ifdef DEBUG        
    _tft->setCursor(18, 160+14);   
    _tft->setFontSize(TFT_eSPI_extended::SmallFont);
    sprintf(buffer,"Target = %d mA",_config->currentDischargeMa);
    _tft->myDrawString(buffer);
    _tft->setCursor(18, 160);       
    sprintf(buffer,"Gate  = %d ",gateCommand);
   _tft->myDrawString(buffer);   
   _tft->setCursor(160, 160+14*1);   
   _tft->setFontSize(TFT_eSPI_extended::SmallFont);
   sprintf(buffer,"Wires = %d mO",_config->userSettings.resistor1000);
   _tft->myDrawString(buffer);
   
   _tft->setFontSize(TFT_eSPI_extended::MediumFont);

#endif
}
/**
 */
batScreen *spawnNewDischarging(batConfig *c, int currentV)
{
    return new dischargingScreen(c,currentV);
}
/**
 * \brief make sure we done exceed MAX_WATT
 * @param currentV
 * @return 
 */
bool     dischargingScreen::evaluateTargetAmp()
{
    // current V cannot be zero ! 800 mV at least
    float maxAmp=(1000.*1000.*BAT_MAX_WATT)/2500.; // in mA
    if(maxAmp<_config->targetDischargeMa)
        _config->currentDischargeMa=50+100*floor(maxAmp/100);
    else
        _config->currentDischargeMa=_config->targetDischargeMa;
    return true;
}
/**
 * \brief Compute the value to send to the DAC driving the IRLZ44N so that we have the wanted 
 * current. This is just an approximation, we'll adjust on the fly later on.
 * @param amp
 * @return 
 */
int     dischargingScreen::computeGateCommand(int amp)
{
    // Command=1.38*a+1443
    float v=amp;
    if(amp<200)
    {
        v=2*v+1440.;
         //v=v*1.28+1525.;
    }else
    if(amp<1100)
    {
        v=v*1.28+1525.;
    }else
    {
        v=v*1.38+1443.;
    }
    if(v>4095) 
        v=4095;    
    return (int)v;
}

// EOF
