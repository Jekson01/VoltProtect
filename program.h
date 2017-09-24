#ifndef _PROGRAM_H_
#define _PROGRAM_H_

#include <inttypes.h>
#include "ind7seg.h"
#include "buttons.h"
#include "macros.h"
#include "voltmeter.h"
#include "delay.h"
#include "hardware.h"
#include "eeprom.h"

#define DELAY_SCR_NAME  4
#define DELAY_SCR_VALUE 10

#define U_UP_MAX        270
#define U_UP_MIN        230
#define U_DN_MAX        210
#define U_DN_MIN        130
#define T_MAX           999
#define T_MIN           1

namespace PRG{
    extern uint16_t maxVoltage;
    extern uint16_t minVoltage;
    extern uint16_t delayOn;
    extern uint8_t autoCalibrateEnable;
    uint8_t protect();
    void editParams();
    void calibrate();
    void loadDefault();
    void autoCalibrate();
}

#endif /* _PROGRAM_H_ */