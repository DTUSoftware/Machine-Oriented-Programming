#include <stdio.h>

int main(void)
{
    int x = 0;
    int y = 0;
    char label[10];

    scanf("%d %d", &x, &y);
    scanf("%s", label);

    printf("%d %d %s", x, y, label);
    return 0;
}
