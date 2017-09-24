#ifndef _RELAY_OUT_H_
#define _RELAY_OUT_H_
#include "device.h"
#include "ind7seg.h"

#define RELAY_INIT()    PA_DDR_bit.DDR3 = 1;\
                        PA_CR1_bit.C13 = 1
#define RELAY(x)      PA_ODR_bit.ODR3 = x

namespace RELAY{
    void initialize();
    void setDelayOn(uint16_t t);
    void update();
    void off();
}
#endif /* _RELAY_OUT_H_ */