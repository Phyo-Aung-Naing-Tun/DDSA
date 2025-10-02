//
// Created by phyo-aung-naing-tun on 9/17/25.
// Pointer
//

/**
 * Definition
 * Pointer store the address of another variable
 */

#include <stdio.h>

int main() {
    int a = 10;

    int *ptr = &a;

    printf("Value of a %d\n", a);
    printf("Address of a %d\n", &a);
    printf("Value of ptr %d\n", *ptr);
    printf("address of ptr Value %d\n", ptr);
    printf("Address of ptr %d\n", &ptr);

    return 0;
}

