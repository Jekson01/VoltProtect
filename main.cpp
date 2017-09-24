#include "hardware.h"
#include "macros.h"
#include <inttypes.h>
#include "ind7seg.h"
#include "buttons.h"
#include "program.h"
#include "voltmeter.h"
#include "relayout.h"
#include "delay.h"
#include "eeprom.h"

// interrupts ---------------------
// blink
ISR(TIM2_OVR_handler, TIM2_OVR_UIF_vector){
    HW::watchdogUpdate();
    DISPLAY::blink();
    RELAY::update();
    DELAY::tick();
    TIM2_SR1_bit.UIF = 0;
}


// Show symbols 
ISR(TIM1_OVR_handler, TIM1_OVR_UIF_vector){
    DISPLAY::updateFast();
    TIM1_SR1_bit.UIF = 0;
}

ISR(TIM1_CAPCOM_CC1IF_handler, TIM1_CAPCOM_CC1IF_vector){
    
    // Off all symbols and catods
    if (TIM1_SR1_bit.CC1IF == 1){
        DISPLAY::offFast();
        BTN_ENABLE();
        TIM1_SR1_bit.CC1IF = 0;
    }
    
    // Check buttons state
    if (TIM1_SR1_bit.CC2IF == 1){
        BTN::update();
        TIM1_SR1_bit.CC2IF = 0;
    }
    //TIM1_SR1_bit.CC2IF = 0;
    
}

/*
ISR(TIM1_CAPCOM_CC2IF_handler, TIM1_CAPCOM_CC2IF_vector){
    BTN::update();
    
}*/
    
ISR(ADC, ADC1_EOC_vector)
{
  unsigned int result;
  result = ADC_DRH << 8;
  result |= ADC_DRL;
  
  //result = ADC_DB9RH << 8;
  //result |= ADC_DB9RL;
  VOLTMETR::add(result);
  ADC_CSR_bit.EOC = 0;          //—бросим признак прерывани€
}

typedef enum PRG_MODE{modeRun, modeCalibrate, modeSetup}PRG_MODE;

int main()
{
    // Initialize hardware
    EEPROM::load();
    
    HW::initialize();
    RELAY::initialize();
    DISPLAY::initialize();
    
    // check calibrate or load default:
    while(1){
        DELAY::ms250(3);
        uint8_t keyCode = BTN::getState();
        if (keyCode == keyLeft){
            if (BTN::isLongPress(3)){
                PRG::calibrate();
                break;
            }
        }
        
        if (keyCode == keyRight){
            PRG::loadDefault();
            break;
        }
        
        if (keyCode == keyNone)
            break;
    }
    
    
    
    RELAY::setDelayOn(PRG::delayOn);
    VOLTMETR::reset();
    while(1){        
        if (PRG::protect() == 1){
            RELAY::setDelayOn(PRG::delayOn);
        }
        
        uint8_t keyCode = BTN::getState();
       
        if (keyCode == keyLeft){ 
            if (BTN::isLongPress()){
                RELAY::off();
                DISPLAY::blinkOn(OFF);
                PRG::editParams();
                RELAY::setDelayOn(PRG::delayOn);
                VOLTMETR::reset();
            }
        }
        
        if (keyCode == keyRight){
            if (BTN::isLongPress())
            {
                if (PRG::autoCalibrateEnable != AUTO_CAL_DISABLE)
                {
                    RELAY::off();
                    DISPLAY::blinkOn(OFF);
                    PRG::autoCalibrate();
                }
            }
        }
    }
    return 0;
}
