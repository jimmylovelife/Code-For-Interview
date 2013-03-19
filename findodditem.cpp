/**
   数组里只有一个是奇数个其他都是偶数个 
*/

#include <stdio.h>
#include <stdlib.h>

/**
   先解决数组里数是1-n,就缺一个数，找出来 
*/

void findMiss(int array[], int len, int min, int max) {
     int t = 0;
     for ( int i=min; i<=max; i++) {
         t = t^ i;
     }
     for (int i=0; i<len; i++) {
         t = t ^ array[i];
     }
     printf("miss item is: %d\n", t);
} 


void findOddItem(int *array, int len) {
     int t = 0;
     for (int i=0; i<len; i++) {
         t = t ^ array[i];
     }
     printf("Odd item is %d\n", t);
}


int main(){
    int a[] = {1,3,6,8,2,4,5,7,9,11};
    findMiss(a, 10, 1, 11);
    int b[] = {1,3,5,3,1,2,5,2,5};
    findOddItem(b,9);
    system("pause");
}
