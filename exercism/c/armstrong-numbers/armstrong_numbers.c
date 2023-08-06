#include "armstrong_numbers.h"
#include <stdbool.h>
#include <stdio.h>

int opow(int num, int k){
    int prod = 1;
    for(int i=0;i<k;i++){
        prod *= num;
    }
    return prod;
}

int get_number_digits(int candidate){
    int num_digits = 0;
    int div = candidate;
    if (div == 0)
        return num_digits++;
    while(div != 0){
        div = candidate/opow(10, num_digits+1);
        num_digits++;
    }
    return num_digits;
}

bool is_armstrong_number(int candidate) {
    int digit = 0, div=candidate, k=0, sum=0;
    int num_digits = get_number_digits(candidate);

    while(div != 0){
        digit = div%10;
        div = candidate/opow(10, k+1);
        //printf("number %i^%i\n", digit, num_digits);
        sum += opow(digit, num_digits);
        k++;
    }

    //printf("number %i, %i\n", candidate, sum);
    return (sum == candidate) ? true:false;
}
