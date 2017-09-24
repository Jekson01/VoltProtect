#ifndef _BUTTONS_H_
#define _BUTTONS_H_
#include "device.h"


#define BTN_LEFT        PC_IDR_bit.IDR3
#define BTN_RIGHT       PD_IDR_bit.IDR5

#define BTN_ENABLE()    PC_DDR_bit.DDR3 = 0;\
                        PC_ODR_bit.ODR3 = 1;\
                        PD_DDR_bit.DDR5 = 0;\
                        PD_ODR_bit.ODR5 = 1
                           
#define BTN_DISABLE()   PC_DDR_bit.DDR3 = 1;\
                        PC_ODR_bit.ODR3 = 0;\
                        PD_DDR_bit.DDR5 = 1;\
                        PD_ODR_bit.ODR5 = 0
                           
#define LONG_PRESS_DELAY        10
#define PRESS_DELAY             50
#define MIN_PRESS_DELAY         5
                            
typedef enum KEYCODES{keyNone = 0, keyLeft = 1, keyRight = 2, keyTwo = 3} KEYCODES;
namespace BTN{
    void update();
    uint8_t getState();
    uint8_t isLongPress();
    uint8_t isLongPress(uint8_t count);
}

#endif /* _BUTTONS_H_ */