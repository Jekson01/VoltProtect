#ifndef _VOLTMETER_H_
#define _VOLTMETER_H_
#include <inttypes.h>
#include "ind7seg.h"

#define TRASHHOLD_LEVEL 10
#define SUM_ADC_COUNT   120

namespace VOLTMETR{
    extern uint16_t koef; // default = 909
    void add(uint16_t data);
    uint8_t readyVoltage();
    uint16_t getVoltage();
    void print();
    void reset();
}

#endif /* _VOLTMETER_H_ */