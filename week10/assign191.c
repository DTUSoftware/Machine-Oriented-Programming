#include <stdio.h>

struct node {
    int count;
    struct node *next;
    int index;
    };

int main(void)
{
    int data = 0;
    struct node *getdata;
    getdata -> count = data + 1;
    printf("%d", getdata -> count);

    return 0;
}
