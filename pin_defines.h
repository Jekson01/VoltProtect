#ifndef _PINDEFINES_H_
#define _PINDEFINES_H_

#include "device.h"

#ifdef DIN_STM_02

#define SEG_A(x)  PC_ODR_bit.ODR3 = x
#define DDR_A() PC_DDR_bit.DDR3 = 1;\
                PC_CR1_bit.C13 = 1

#define SEG_B(x)  PC_ODR_bit.ODR6 = x
#define DDR_B() PC_DDR_bit.DDR6 = 1; \
                PC_CR1_bit.C16 = 1

#define SEG_C(x)  PC_ODR_bit.ODR7 = x
#define DDR_C() PC_DDR_bit.DDR7 = 1;\
                PC_CR1_bit.C17 = 1

#define SEG_D(x)  PD_ODR_bit.ODR2 = x
#define DDR_D() PD_DDR_bit.DDR2 = 1;\
                PD_CR1_bit.C12 = 1

#define SEG_E(x)  PD_ODR_bit.ODR3 = x
#define DDR_E() PD_DDR_bit.DDR3 = 1;\
                PD_CR1_bit.C13 = 1

#define SEG_F(x)  PC_ODR_bit.ODR4 = x
#define DDR_F() PC_DDR_bit.DDR4 = 1;\
                PC_CR1_bit.C14 = 1

#define SEG_G(x)  PA_ODR_bit.ODR3 = x
#define DDR_G() PA_DDR_bit.DDR3 = 1;\
                PA_CR1_bit.C13 = 1

#define SEG_H(x)  PD_ODR_bit.ODR1 = x
#define DDR_H() PD_DDR_bit.DDR1 = 1;\
                PD_CR1_bit.C11 = 1

#define SEG_D3(x)  PB_DDR_bit.DDR5 = x

#define SEG_D2(x)  PB_DDR_bit.DDR4 = x

#define SEG_D1(x)  PC_DDR_bit.DDR5 = x
                    
#define BTN_LEFT        PC_IDR_bit.IDR7
#define BTN_RIGHT       PA_IDR_bit.IDR3

#define BTN_ENABLE()    PC_DDR_bit.DDR7 = 0;\
                        PC_ODR_bit.ODR7 = 1;\
                        PA_DDR_bit.DDR3 = 0;\
                        PA_ODR_bit.ODR3 = 1
                           
#define BTN_DISABLE()   PC_DDR_bit.DDR7 = 1;\
                        PC_ODR_bit.ODR7 = 0;\
                        PA_DDR_bit.DDR3 = 1;\
                        PA_ODR_bit.ODR3 = 0

#define RELAY_INIT()    PD_DDR_bit.DDR4 = 1;\
                        PD_CR1_bit.C14 = 1
#define RELAY(x)      PD_ODR_bit.ODR4 = x
                            
#define ADC_PIN         5
#define TERM_PIN        6
#endif
//-----------------------------------------------------------------------------

#ifdef EVRO_STM
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

#define RELAY_INIT()    PA_DDR_bit.DDR3 = 1;\
                        PA_CR1_bit.C13 = 1
#define RELAY(x)        PA_ODR_bit.ODR3 = x

#define ADC_PIN         2

#endif
//-----------------------------------------------------------------------------                            
#endif /* _PINDEFINES_H_ */