#include <stdio.h>
int main(void){
    int i = 0;
    int sum = 0;
    while (i<11){
        sum = sum + i++;
    }
    printf("%d\n", sum);
}