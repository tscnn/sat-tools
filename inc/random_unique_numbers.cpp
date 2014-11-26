#include <stdlib.h>

/**
 * Generating an array with random unique ints.
 * Warning: Time complexity is linear in range.
 * 
 * length: size of the array
 * range_start: min value
 * range_end: max value    
 */ 
int* random_unique_ints(int range_start, int range_end, int length)
{
    int* array = new int[length];
    int range = range_end - range_start + 1;

    //knuth algorithm
    int r,s;
    for(int i=0,j=0; i<range && j<length; i++) {
        r = range - i;
        s = length - j;
        if (rand() % r < s)    
            array[j++] = i + range_start;
    }
    
    //fisher–yates shuffle
    int tmp,r;
    for(int i=0; i<length; i++){
        r = rand() % length;
        tmp = array[i];
        array[i] = array[r];
        array[r] = tmp;
    }
    
    return array;
}