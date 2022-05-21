#include <stdio.h>

int t = 1;

int subl1(int fluff);

int main(void){
    int t = 2;
    int z;
    z = z + 1;
    printf("A: the variable z equals %d\n", z);
    {
        z = t;
        t = 3;
        {
            int t = 4;
            z = t;
            z = z + 1;
            printf("B: the variable z equals %d\n", z);
        }
        z = subl1(z);
        z = z + 1;
        printf("C: the variable z equals %d\n", z);
    }
    z = t;
    z = z + 1;
    printf("D: the variable z equals %d\n", z);
}
int subl1(int fluff){
    int i;
    i = t;
    return (fluff + 1);
}