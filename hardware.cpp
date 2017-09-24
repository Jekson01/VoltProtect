#include "hardware.h"

void HW::initialize(){
    
    // CPU init
    CLK_CKDIVR_bit.HSIDIV = HSI_4MHz;
    CLK_CKDIVR_bit.CPUDIV = 0;
    while (CLK_ICKR_bit.HSIRDY != 1){}
    
    /*
    // IO setup
    PA_DDR_bit.DDR3 = 1;
    PA_CR1_bit.C13 = 1;
    
    
    
    PC_DDR = 0xE8;
    PC_CR1 = 0xE8;
    
    PD_DDR = 0x2F;
    PD_CR1 = 0x2F;
    
    // Catod outs
    PB_DDR_bit.DDR4 = 1;
    PB_DDR_bit.DDR5 = 1;
    PD_DDR_bit.DDR4 = 1;
    */
        
    timersInitialize();
    adcInitialize();
    
    sei();
    watchdogInitialize();
}

void HW::timersInitialize(){
    // Timer 4 init
    /*
    TIM4_SR_bit.UIF = 0;
    TIM4_PSCR = 0x05;
    //TIM4_ARR = 125;
    TIM4_IER_bit.UIE = 1;
    TIM4_CR1_bit.CEN = 1;
    */
    
    // Timer 1 init for display and buttons check
    TIM1_SR1_bit.UIF = 0;
    
    TIM1_PSCRH = (1000) >> 8;
    TIM1_PSCRL = (1000) & 0xFF; //Делитель на 200
    
    TIM1_ARRH = (19) >> 8; //Частота переполнений = 4М / 200 / 10 = 2 kГц
    TIM1_ARRL = (19)& 0xFF;

    
    TIM1_IER_bit.UIE = 1;
    
    TIM1_CCR1H = (17) >> 8;
    TIM1_CCR1L = (17) & 0xFF;
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
    ADC_TDRL |= (1 << 2);
    ADC_CSR_bit.CH = 2; // AIN 2
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