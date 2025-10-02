//
// Created by phyo-aung-naing-tun on 9/17/25.
//

#include <stdio.h>

int main() {
    int arr[5] = {1,2,3,4,5};
    int *ptr = &arr;

    for (int x = 0; x < 5; x++) {
        printf("Value Of Arr %d\n", (ptr + 2));
    }
        printf("Value Of Arr %d\n", ptr);




    return 0;
}