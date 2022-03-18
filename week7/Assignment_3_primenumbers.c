#include <stdio.h>

void main(){
    int min, max, isPrime;
    printf("input a minimum and maximum value\n");
    scanf("%d %d", &min, &max);
    printf("input was min = %d max = %d \n", min, max);
    for (int i = min+1; i < max; i++){
        isPrime = 1;
        for (int j = 2; j*j <= i; ++j ){
            if (i%j==0){
                isPrime = 0;
                break;
            }
        }
        if (isPrime == 1){
            printf("%d \n", i);
        }
    }
}