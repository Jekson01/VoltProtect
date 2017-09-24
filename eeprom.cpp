#include "eeprom.h"
#include "crc.h"

namespace EEPROM{
    
    #pragma location=0x4000
    __no_init EParam eParam[MEM_COPY_COUNT];
}

void EEPROM::save(uint8_t num){
    
    CRC crc;
    
    if (eParam[num].autoCalibrateEnable != PRG::autoCalibrateEnable)
        eParam[num].autoCalibrateEnable = PRG::autoCalibrateEnable;
    crc.add8(PRG::autoCalibrateEnable);
    
    if (eParam[num].upVoltage != PRG::maxVoltage)
        eParam[num].upVoltage = PRG::maxVoltage;
    crc.add16(PRG::maxVoltage);
    
    if (eParam[num].downVoltage != PRG::minVoltage)
        eParam[num].downVoltage = PRG::minVoltage;
    crc.add16(PRG::minVoltage);
    
    if (eParam[num].delayOn != PRG::delayOn)
        eParam[num].delayOn = PRG::delayOn;
    crc.add16(PRG::delayOn);
    
    if (eParam[num].scaleVoltage != VOLTMETR::koef)
        eParam[num].scaleVoltage = VOLTMETR::koef;
    crc.add16(VOLTMETR::koef);
    
    if (eParam[num].crc != crc.getCRC8())
        eParam[num].crc = crc.getCRC8();
}

void EEPROM::save(){
    EEPROM_ENABLE();
    
    for (uint8_t i = 0; i < MEM_COPY_COUNT; i++){
        save(i);
    }
    
    EEPROM_DISABLE();
}

uint8_t EEPROM::load(uint8_t num){

    CRC crc;
    PRG::autoCalibrateEnable = eParam[num].autoCalibrateEnable;
    crc.add8(PRG::autoCalibrateEnable);
    
    PRG::maxVoltage = eParam[num].upVoltage;
    crc.add16(PRG::maxVoltage);
    
    PRG::minVoltage = eParam[num].downVoltage;
    crc.add16(PRG::minVoltage);
    
    PRG::delayOn = eParam[num].delayOn;
    crc.add16(PRG::delayOn);
    
    VOLTMETR::koef = eParam[num].scaleVoltage;
    crc.add16(VOLTMETR::koef);
    
    uint8_t crc = eParam[num].crc;
    
    if (crc != 0)
    return 0;
}

void EEPROM::load(){

}