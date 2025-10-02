//
// Created by phyo-aung-naing-tun on 9/29/25.
// Reference Pass By Pointer
//

#include <stdio.h>

void reference(int *a, int *b);

int main() {

    int a = 10;
    int b = 20;

	printf("Before Calling Function a = %d, b = %d\n", a, b);

    reference(&a,&b);

    printf("After Calling Function a = %d, b = %d\n", a, b);

    return 0;
}

void reference(int *a, int *b) {
    int temp;
    temp = *b;
    *b = *a;
    *a = temp;


}

