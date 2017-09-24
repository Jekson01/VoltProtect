#include "program.h"

namespace PRG{
    uint16_t maxVoltage = DEF_U_UP;
    uint16_t minVoltage = DEF_U_DN;
    uint16_t delayOn = DEF_T_ON;
    uint8_t autoCalibrateEnable = 0;

}

uint8_t PRG::protect(){
    if (VOLTMETR::readyVoltage()){
        uint16_t voltage = VOLTMETR::getVoltage();
        VOLTMETR::print();
        if (voltage > maxVoltage)
            return 1;
        
        if (voltage < minVoltage)
            return 1;
    }
    
    return 0;
}

void PRG::editParams(){
    // Print UuP
    DISPLAY::digits[0] = S_U;
    DISPLAY::digits[1] = S_u;
    DISPLAY::digits[2] = S_P;
    DELAY::ms250(DELAY_SCR_NAME);
    BTN::getState();
    
    // Edit UuP
    DELAY::setDelay(DELAY_SCR_VALUE);
    while(DELAY::isRun()){
        uint8_t btnState = BTN::getState();
        if (btnState != keyNone){
            if (btnState == keyLeft){
                if (maxVoltage > U_UP_MIN)
                    maxVoltage--;
            }
                
            if (btnState == keyRight){
                if (maxVoltage < U_UP_MAX)
                    maxVoltage++;
            }
            DELAY::setDelay(DELAY_SCR_VALUE);
        }
        DISPLAY::print(maxVoltage);
    }

    // Print Udn
    DISPLAY::digits[0] = S_U;
    DISPLAY::digits[1] = S_d;
    DISPLAY::digits[2] = S_n;
    DELAY::ms250(DELAY_SCR_NAME);
    
    // Edit Udn
    DELAY::setDelay(DELAY_SCR_VALUE);
    while(DELAY::isRun()){
        uint8_t btnState = BTN::getState();
        if (btnState != keyNone){
            if (btnState == keyLeft){
                if (minVoltage > U_DN_MIN)
                    minVoltage--;
            }
                
            if (btnState == keyRight){
                if (minVoltage < U_DN_MAX)
                    minVoltage++;
            }
            DELAY::setDelay(DELAY_SCR_VALUE);
        }
        DISPLAY::print(minVoltage);
    }
    
    // Print t
    DISPLAY::digits[0] = S_CLEAR;
    DISPLAY::digits[1] = S_t;
    DISPLAY::digits[2] = S_CLEAR;
    DELAY::ms250(DELAY_SCR_NAME);
    
    // Edit t
    DELAY::setDelay(DELAY_SCR_VALUE);
    while(DELAY::isRun()){
        uint8_t btnState = BTN::getState();
        if (btnState != keyNone){
            if (btnState == keyLeft){
                if (delayOn > T_MIN)
                    delayOn--;
            }
                
            if (btnState == keyRight){
                if (delayOn < T_MAX)
                    delayOn++;
            }
            DELAY::setDelay(DELAY_SCR_VALUE);
        }
        DISPLAY::print(delayOn);
    }
    DISPLAY::digits[0] = S_CLEAR;
    DISPLAY::digits[1] = S_CLEAR;
    DISPLAY::digits[2] = S_CLEAR;
    EEPROM::save();
    HW::reset();
}

void PRG::calibrate(){
    
    DISPLAY::digits[0] = S_C;
    DISPLAY::digits[1] = S_A;
    DISPLAY::digits[2] = S_L;
    
    DELAY::ms250(DELAY_SCR_NAME);
    BTN::getState();
    
    DELAY::setDelay(DELAY_SCR_VALUE * 2);
    VOLTMETR::reset();
    while(1){
        if (VOLTMETR::readyVoltage()){
            VOLTMETR::print();
        }
        
        uint8_t keyState = BTN::getState();
        if (keyState != keyNone){
            DELAY::setDelay(DELAY_SCR_VALUE * 2);
            if (keyState == keyLeft)
                VOLTMETR::koef--;
            
            if (keyState == keyRight){
                VOLTMETR::koef++;
            }
            
        }
        if (DELAY::isRun() == 0)
            break;
    }
    
    // save in EEPROM
    DISPLAY::print(VOLTMETR::koef);
    DELAY::ms250(6);
    loadDefault();
}

void PRG::loadDefault(){
    DISPLAY::digits[0] = S_d;
    DISPLAY::digits[1] = S_E;
    DISPLAY::digits[2] = S_F;
    DELAY::ms250(DELAY_SCR_NAME);
    maxVoltage = DEF_U_UP;
    minVoltage = DEF_U_DN;
    delayOn = DEF_T_ON; 
    EEPROM::save();
    HW::reset();
}

void PRG::autoCalibrate(){
    DISPLAY::digits[0] = S_A;
    DISPLAY::digits[1] = S_u;
    DISPLAY::digits[2] = S_t;
    DELAY::ms250(DELAY_SCR_NAME);
    VOLTMETR::reset();
    while(1){
        if (VOLTMETR::readyVoltage()){
            uint16_t voltage = VOLTMETR::getVoltage();
            if (voltage < 220)
                VOLTMETR::koef++;
            
            if (voltage > 220)
                VOLTMETR::koef--;
            
            if (voltage == 220){
                autoCalibrateEnable = AUTO_CAL_DISABLE;
                loadDefault();
            }
            VOLTMETR::print();
        }
    }
}