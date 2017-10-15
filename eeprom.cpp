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
    
    if (eParam[num].bright != PRG::bright)
        eParam[num].bright = PRG::bright;
    crc.add8(PRG::bright);
    
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
    uint8_t dataError = 0;
    CRC crc;
    
    PRG::autoCalibrateEnable = eParam[num].autoCalibrateEnable;
    crc.add8(PRG::autoCalibrateEnable);
    
    PRG::bright = eParam[num].bright;
    crc.add8(PRG::bright);
    if (PRG::bright == 0)
        dataError++;
    
    PRG::maxVoltage = eParam[num].upVoltage;
    crc.add16(PRG::maxVoltage);
    if (PRG::maxVoltage == 0)
        dataError++;
    
    PRG::minVoltage = eParam[num].downVoltage;
    crc.add16(PRG::minVoltage);
    if (PRG::minVoltage == 0)
        dataError++;
    
    PRG::delayOn = eParam[num].delayOn;
    crc.add16(PRG::delayOn);
    if (PRG::delayOn == 0)
        dataError++;
    
    VOLTMETR::koef = eParam[num].scaleVoltage;
    crc.add16(VOLTMETR::koef);
    if (VOLTMETR::koef == 0)
        dataError++;
    
    uint8_t tmpCrc = eParam[num].crc;
    crc.add8(tmpCrc);
    
    if (dataError != 0)
        return 1;
    
    if (crc.getCRC8() != 0)
        return 1;
    
    return 0;
}

void EEPROM::load(){
    for (uint8_t i = 0; i < MEM_COPY_COUNT; i++){
        if (load(i) == 0)
        {
            if (i != 0)
                save();
            
            return;
        }
    }
    
    PRG::autoCalibrateEnable = 0xFF;
    PRG::bright = DEF_BRIGHT;
    PRG::maxVoltage = DEF_U_UP;
    PRG::minVoltage = DEF_U_DN;
    PRG::delayOn = DEF_T_ON;
    VOLTMETR::koef = DEF_K_ADC;
    save();
}