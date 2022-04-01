#include <stdio.h>
int main(void){
    char echo = '0';

    while (echo != '\n'){
        scanf("%c", &echo);
        if ((echo >= 'a' && echo <= 'z' ) || (echo >= 'A' && echo <= 'Z'))
            printf("%c", echo);
    }
}