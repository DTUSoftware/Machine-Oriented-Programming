#include <stdio.h>
int main(void){
    
    int nextInput;
    scanf("%d", &nextInput);
    //no longer initializes smalles number as 1 but as the the input +1 to make sure it stores
    // all the inputs 
    int smallestNumber = nextInput+1;

    while (nextInput != -1){
        if (nextInput < smallestNumber){
            smallestNumber = nextInput;
        }
        scanf("%d", &nextInput);
    }
    printf("the smalles number is %d\n", smallestNumber);
}