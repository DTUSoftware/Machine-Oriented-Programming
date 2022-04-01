#include <stdio.h>

typedef struct {
    int *arr;
    int len;
} Array;

int get(Array arr, int i, int *store) {
    if (i < 0 || i >= arr.len) {
        return -1;
    }
    *store = arr.arr[i];
    return 0;
}

int put(Array arr, int i, int put) {
    if (i < 0 || i >= arr.len) {
        return -1;
    }
    arr.arr[i] = put;
    return 0;
}

int main() {
    int length = 5;
    int arr[length];
    arr[0] = 0;
    arr[1] = 1;
    arr[2] = 2;
    arr[3] = 3;

    Array array;
    array.arr = arr;
    array.len = length;

    int i;
    int store;
    int err;
    printf("Getting...\n");
    for (i = -1; i < length*2; i++) {
        store = 0;
        err = get(array, i, &store);
        if (err != 0) {
            printf("Index out of bounds - i = %d!\n", i);
            continue;
        }
        printf("arr[%d] = %d\n", i, store);
    }

    int to_put;
    printf("Putting...\n");
    for (i = 4; i < length*2; i++) {
        to_put = i*2;
        err = put(array, i, to_put);
        if (err != 0) {
            printf("Index out of bounds - i = %d!\n", i);
            continue;
        }
        printf("arr[%d] = %d\n", i, to_put);
    }

    return 0;
}
