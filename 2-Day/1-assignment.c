//
// Created by phyo-aung-naing-tun on 8/19/25.
// 1 Assignment
//
#include <stdio.h>

int main() {
    int x = 0;
    int y = 0;
    int z = 0;
    int stop = 10;

    for(x = 1; x <= stop; x++){
        for(y = 0; y < stop - x ; y++){
            printf(" ");
        };

        for( z = 0; z < (2 * x - 1); z++){
            printf("*");
        };

        for(y = 0; y < 2 * (stop - x); y++){
            printf(" ");
        };

        for( z = 0; z < (2 * x - 1); z++){
            printf("*");
        };

        printf("\n");
    };

    return 0;
}