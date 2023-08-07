#include "hamming.h"
#include <stdio.h>

int compute(const char *lhs, const char *rhs){
    int count = 0;

    while(*lhs && *rhs){

        if (*lhs != *rhs){
            count++;
        }

        lhs++;
        rhs++;

    }

    return (*lhs || *rhs) ? -1 : count;
}
