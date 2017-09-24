#ifndef _DELAY_H_
#define _DELAY_H_

#include <inttypes.h>

namespace DELAY{
    void tick();
    void ms250(uint16_t time);
    void setDelay(uint16_t time);
    uint16_t isRun();
}

#endif /* _DELAY_H_ */