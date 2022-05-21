#include <stdio.h>
#define MAX_SIZE 10

int main() {
    int index;
    int array[MAX_SIZE];
    int limit;

    printf("Enter a limit (integer):");
    scanf("%d", &limit);
    if (limit >= MAX_SIZE){
        printf("limit too big try something smalle than %d", MAX_SIZE);
        scanf("%d", &limit);
    }

    for (index = 0; index < limit;index++){
        array[index] = 0;
        printf("array[%d] is set to 0\n", index);
    }
        return 0;
}
