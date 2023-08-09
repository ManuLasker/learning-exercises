#include "difference_of_squares.h"

unsigned int sum_of_squares(unsigned int number){
    unsigned int sum = ((number+1)*(2*number+1)*number+2)/6 ;
    return sum;
}

unsigned int square_of_sum(unsigned int number){
    unsigned int sum = ((number + 1) * number) / 2;
    return sum * sum;
}

unsigned int difference_of_squares(unsigned int number){
    return  square_of_sum(number) - sum_of_squares(number);
}
