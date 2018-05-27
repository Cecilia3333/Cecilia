#include <stdio.h>

int count_one_bits(unsigned value){
    int ones = 0;
    for(;value != 0;value = value >> 1){
        if(value % 2 != 0)
            ones += 1;
    }
    return ones;
}


int count_one_bits(unsigned value){
    int ones = 0;
    for(;value != 0;value >>= 1){
        if((value & 1) != 0)
            ones += 1;
    }
    return ones;
}
