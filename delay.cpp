#include "delay.h"

namespace DELAY{
    uint16_t counter = 0;
}

void DELAY::tick(){
    if (counter > 0)
        counter--;
}

void DELAY::ms250(uint16_t time){
    counter = time;
    while(counter){}
}

void DELAY::setDelay(uint16_t time){
    counter = time;
}

uint16_t DELAY::isRun(){
    return counter;
}