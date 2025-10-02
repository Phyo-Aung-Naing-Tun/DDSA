//
// Created by phyo-aung-naing-tun on 9/2/25.
// Structures
//

#include "stdio.h"

struct People {
    char name[20];
    char email[20];
    char password[20];
    int phone;
};

struct People student[3];

int main() {

    printf("Please enter student name:\n");
    scanf(" %[^\n]", &student[0].name);

    printf("Please enter student email:\n");
    scanf(" %[^\n]", &student[0].email);

    printf("Please enter student password:\n");
    scanf(" %[^\n]", &student[0].password);

    printf("Please enter student phone:\n\n");
    scanf("%d", &student[0].phone);

    printf("Student Name is: %s\n", student[0].name);
    printf("Student Email is: %s\n", student[0].email);
    printf("Student Password is: %s\n", student[0].password);
    printf("Student Phone is: %d\n", student[0].phone);


    return 0;
}