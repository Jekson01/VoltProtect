#ifndef _IND7SEG_H_
#define _IND7SEG_H_
#include "device.h"

#define ON      1
#define OFF     0

#define SEG_A(x)  PC_ODR_bit.ODR3 = x
#define DDR_A() PC_DDR_bit.DDR3 = 1;\
                PC_CR1_bit.C13 = 1

#define SEG_B(x)  PD_ODR_bit.ODR5 = x
#define DDR_B() PD_DDR_bit.DDR5 = 1; \
                PD_CR1_bit.C15 = 1

#define SEG_C(x)  PD_ODR_bit.ODR3 = x
#define DDR_C() PD_DDR_bit.DDR3 = 1;\
                PD_CR1_bit.C13 = 1

#define SEG_D(x)  PC_ODR_bit.ODR7 = x
#define DDR_D() PC_DDR_bit.DDR7 = 1;\
                PC_CR1_bit.C17 = 1

#define SEG_E(x)  PC_ODR_bit.ODR6 = x
#define DDR_E() PC_DDR_bit.DDR6 = 1;\
                PC_CR1_bit.C16 = 1

#define SEG_F(x)  PC_ODR_bit.ODR5 = x
#define DDR_F() PC_DDR_bit.DDR5 = 1;\
                PC_CR1_bit.C15 = 1

#define SEG_G(x)  PD_ODR_bit.ODR2 = x
#define DDR_G() PD_DDR_bit.DDR2 = 1;\
                PD_CR1_bit.C12 = 1

#define SEG_H(x)  PD_ODR_bit.ODR1 = x
#define DDR_H() PD_DDR_bit.DDR1 = 1;\
                PD_CR1_bit.C11 = 1

#define SEG_D3(x)  PB_DDR_bit.DDR4 = x

#define SEG_D2(x)  PB_DDR_bit.DDR5 = x

#define SEG_D1(x)  PD_DDR_bit.DDR4 = x

#define SEGMENT_COUNT   7
#define DGT_COUNT       3
#define MAX_BRIGHT      12
#define MIN_BRIGHT      1
                    
#define S_CLEAR 10
#define S_U     11
#define S_u     12
#define S_P     13
#define S_d     14
#define S_n     15
#define S_t     16
#define S_C     17
#define S_A     18
#define S_L     19
#define S_MINUS 20
#define S_E     21
#define S_F     22
#define S_b     23
#define S_r     24                    
                    
namespace DISPLAY{
    extern uint8_t digits[DGT_COUNT];
    void initialize();
    void update();
    void updateFast();
    void offFast();
    void onCatode(uint8_t num);
    void offCatode(uint8_t num);
    void onSegment(uint8_t num);
    void offSegment(uint8_t num);
    
    void print(uint16_t num);
    void off();
    void setBright(uint8_t bright);
    
    void blinkOn(uint8_t enable);
    void blink();
}

#endif /* _IND7SEG_H_ */