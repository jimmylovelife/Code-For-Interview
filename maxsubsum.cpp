/**
   数组中和最大的连续子串 
*/
#include <stdlib.h>
#include <stdio.h>
void maxsub(int *array, int len) {
     int start =0, sum=0, max=0, max_start=0, max_end=0;
     for (int i = 0; i < len; i++) {
         sum += array[i];
         if (sum < 0) { 
            start = i+1;
            sum = 0;
         } else if(sum > max) {
            max = sum;
            max_start = start;
            max_end = i;
         } 
     } 
     printf("max: %d, max_start: %d, max_end: %d", max, max_start, max_end);         
}


int main() {
    int s[] = {1,2,-1,3,-5,-1,9,-4,11,-10,5};
    maxsub(s, 11);
    
    system("pause");
    return 0;
}
