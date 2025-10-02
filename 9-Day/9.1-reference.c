//
// Created by phyo-aung-naing-tun on 9/28/25.
// Reference (pass by value)
//


#include <stdio.h>

void pass_by_value(int a, int b);

int main() {

	int a = 10;
	int b = 20;
	printf("Before Calling Function a = %d, b = %d\n", a, b);

	pass_by_value(a,b);

	printf("After Calling Function a = %d, b = %d\n", a, b);

    return 0;
}


void pass_by_value(int a, int b){
	a++;
	b++;
}

