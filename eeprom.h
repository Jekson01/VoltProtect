#ifndef _EEPROM_H_
#define _EEPROM_H_
#include "device.h"
#include "program.h"
#include "voltmeter.h"
#include "inttypes.h"

#define AUTO_CAL_DISABLE        0x55
#define MEM_COPY_COUNT          3

typedef enum {
    noError = 0,
    crcError,
    isFirstLoad
}LoadResult;

typedef struct{
    uint8_t autoCalibrateEnable;
    uint8_t bright;
    uint16_t upVoltage;
    uint16_t downVoltage;
    uint16_t delayOn;
    uint16_t scaleVoltage;
    uint8_t crc;
}EParam;

namespace EEPROM{
    void save(uint8_t num);
    void save();
    uint8_t load(uint8_t num);
    void load();
}

#endif /* _EEPROM_H_ */