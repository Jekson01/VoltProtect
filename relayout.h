#ifndef _RELAY_OUT_H_
#define _RELAY_OUT_H_
#include "device.h"
#include "pin_defines.h"
#include "ind7seg.h"



namespace RELAY{
    void initialize();
    void setDelayOn(uint16_t t);
    void update();
    void off();
}
#endif /* _RELAY_OUT_H_ */