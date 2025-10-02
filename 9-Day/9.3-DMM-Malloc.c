//
// Created by phyo-aung-naing-tun on 9/29/25.
// Malloc and Free
//

#include <stdio.h>
#include <stdlib.h>

int main() {

    int *arr;
    int n = 5;

    *arr = (int*)malloc( n * sizeof(int));

    for (int x = 0; x < n; x++) {
        arr[x] = 100 + x;
    }

    for (int x = 0; x < n; x++) {
        printf(" Value of arr is %d\n", arr[x]);
    }



    return 0;
}
