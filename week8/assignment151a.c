#include<stdio.h>
int main(void){
    int i = 1;
    int sum = 0;
    while (i<11){
        sum = sum + i;
        ++i;
    }
    printf("%d\n", sum);
    
}