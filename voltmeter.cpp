#include "voltmeter.h"

namespace VOLTMETR{
    uint32_t adcSum = 0;
    uint16_t adcCounter = 0;
    uint16_t voltage = 0;
    uint16_t koef = DEF_K_ADC;
    uint8_t isDone = 0;
    uint8_t isNewVawe = 0;
    uint8_t countPeriod = 0;
    uint16_t printVoltage = 0;
    uint8_t printCounter = 0;
}

void VOLTMETR::add(uint16_t data){
    
    if (data > TRASHHOLD_LEVEL){
        if (isNewVawe < 3)
            isNewVawe++;
    }
    
    if (isNewVawe){
        adcCounter++;
        adcSum += data;
        if (adcCounter == SUM_ADC_COUNT){
            countPeriod++;
            adcCounter = 0;
            isNewVawe = 0;
            if (countPeriod == 4){
                countPeriod = 0;
                isDone = 1;
            }
        }
    }
    
}

uint8_t VOLTMETR::readyVoltage(){
    if (isDone){
        isDone = 0;
        voltage = (uint16_t)((adcSum * koef) / 200000);      
        adcSum = 0;
        return 1;
    }
    return 0;
}

uint16_t VOLTMETR::getVoltage(){
    return voltage;
}

void VOLTMETR::print(){
    printVoltage += voltage;
    printCounter++;
    if (printCounter == 10){
        printCounter = 0;
        DISPLAY::print(printVoltage / 10);
        printVoltage = 0;
    }
}

void VOLTMETR::reset(){
    adcSum = 0;
    adcCounter = 0;
    voltage = 0;
    isDone = 0;
    isNewVawe = 0;
    countPeriod = 0;
    printVoltage = 0;
    printCounter = 0;
}