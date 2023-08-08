#include "grains.h"

uint64_t square(uint8_t index){

    switch (index) {
        case 0:
            return 0;
        case 1:
            return 1;
        default:
            return 2ul << (index - 2);
    }

    return 0;
}

uint64_t total(void){
    uint64_t sum = 0;
    for (int i=0; i<=64; i++) {
        sum+=square(i);
    }
    return sum;
}
