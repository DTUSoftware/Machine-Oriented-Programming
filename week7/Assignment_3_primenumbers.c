#include <stdio.h>

void main(){
    int min, max, isPrime;
    scanf("%d", &min);
    scanf("%d", &max);

    printf("min er %d max %d \n", min, max);
    if (min<=1){
        min++;
    }
    if( min <= 2 && 2 <= max){
        printf("%d \n", 2);
        min = 3;
    }
    for (int i = min; i < max; i+=2){
        isPrime = 1;      
        for (int j = 2; j*j <= i; ++j){
            if (i % j == 0){
                isPrime = 0;
                break;
            }
        }
        if (isPrime == 1){
            printf("%d \n", i);
        }
    }
}