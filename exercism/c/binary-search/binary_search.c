#include "binary_search.h"

const int *binary_search(int value, const int *arr, size_t length){
    int l = 0, h = length, m, v;

    if (h == 0)
        return NULL;

    do {
        m = l + ((h - l) >> 1);
        v = arr[m];
        if (value == v){
            return &arr[m];
        }else if (value < v){
            h = m;
        }else if (value > v){
            l = m + 1;
        }
    }while (l < h);

    return NULL;
}
