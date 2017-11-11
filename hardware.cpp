#include "hardware.h"
#include "pin_defines.h"

void HW::initialize(){
    
    // CPU init
    CLK_CKDIVR_bit.HSIDIV = HSI_4MHz;
    CLK_CKDIVR_bit.CPUDIV = 0;
    while (CLK_ICKR_bit.HSIRDY != 1){}
        
    timersInitialize();
    adcInitialize();
    
    sei();
    watchdogInitialize();
}

void HW::timersInitialize(){
    
    // Timer 1 init for display and buttons check
    TIM1_SR1_bit.UIF = 0;
    
    TIM1_PSCRH = (1000) >> 8;
    TIM1_PSCRL = (1000) & 0xFF; //Делитель на 1000
    
    TIM1_ARRH = (19) >> 8; //Частота переполнений = 4М / 1000 / 20 = 100 Гц
    TIM1_ARRL = (19)& 0xFF;

    
    TIM1_IER_bit.UIE = 1;
    
    TIM1_CCR1H = (8) >> 8;
    TIM1_CCR1L = (8) & 0xFF;
    TIM1_IER_bit.CC1IE = 1;
    
    TIM1_CCR2H = (18) >> 8;
    TIM1_CCR2L = (18) & 0xFF;
    TIM1_IER_bit.CC2IE = 1;
    TIM1_CR1_bit.CEN = 1;
    
    // timer2
    TIM2_SR1_bit.UIF = 0;
    TIM2_PSCR_bit.PSC = 0x6;
    TIM2_ARRH = (15624) >> 8;
    TIM2_ARRL = (15624) & 0xFF;
    TIM2_IER_bit.UIE = 1;
    TIM2_CR1_bit.CEN = 1;
}

void HW::adcInitialize(){
    ADC_CR1_bit.ADON = 1;
    ADC_TDRL |= (1 << ADC_PIN);
    ADC_CSR_bit.CH = ADC_PIN; // AIN 5
    ADC_CR1_bit.CONT = 1;
    ADC_CR2_bit.ALIGN = 1;
    ADC_CR1_bit.SPSEL = 7; // F_CPU / 18
    //ADC_CR3_bit.DBUF = 1;
    ADC_CSR_bit.EOCIE = 1;  // Прерывание по завершению преобразования
    ADC_CR1_bit.ADON = 1;
}

void HW::watchdogInitialize(){
    IWDG_KR = 0xAA;
    IWDG_KR = 0xCC;
    IWDG_KR = 0x55;
    
    IWDG_PR_bit.PR = 6;
    IWDG_RLR = 0xFF;
    IWDG_KR = 0xAA;
}

void HW::reset(){
    cli();
}

void HW::watchdogUpdate(){
    IWDG_KR = 0xAA;
}