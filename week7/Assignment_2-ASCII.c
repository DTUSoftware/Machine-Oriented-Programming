#include <stdio.h>

int main(){
    int i = 0;
    int j = 0;
    while (1) {
        j++;
        printf("%c", i);
        if (j >= 10) {
            printf("\r\n");
            j = 0;
        }
        else {
            printf("\t");
        }
        i++;
        if (i > 255) {
            break;
        }
    }

    return 0;
}
