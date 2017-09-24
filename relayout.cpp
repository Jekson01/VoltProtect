#include "relayout.h"

namespace RELAY{
    uint16_t counter = 0;
}

void RELAY::initialize(){
    RELAY_INIT();
    RELAY(OFF);
}

void RELAY::setDelayOn(uint16_t t){
    counter = t * 4 + 1;
    RELAY(OFF);
    DISPLAY::blinkOn(ON);
}

void RELAY::update(){
    if (counter != 0)
        counter--;
    
    if (counter == 1){
        RELAY(ON);
        DISPLAY::blinkOn(OFF);
    }
}

void RELAY::off(){
    RELAY(OFF);
    counter = 0;
}