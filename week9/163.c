#include <stdio.h>
int x;
int main(void)
{
    int *px = &x;
    int x = 7;

    *px = 4;
    printf("z = %d\n", x);
    return 0;
}
