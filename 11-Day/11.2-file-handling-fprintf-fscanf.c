//
// Created by phyo-aung-naing-tun on 10/8/25.
// File handling fprintf() and fscanf();
//

#include "stdio.h"
#include "stdlib.h"

typedef struct Student {
    char name[10];
    int age;
}Student;

int main() {

    Student s1 = {"Aung",30};
    Student s2;

    FILE *fptr;

    fptr = fopen("test.txt","w");

    if (fptr == NULL) {
        perror("\n");
        return -1;
    }else {
        printf("file opened successfully\n");
        fprintf(fptr,"%s %d\n",s1.name,s1.age);
        printf("file wrote successfully\n");
        fclose(fptr);
    }

    fptr = fopen("test.txt","r");

    if (fptr == NULL) {
        perror("\n");
        return -1;
    }else {
        printf("file opened successfully\n");
            fscanf(fptr,"%s %d",&s2.name,&s2.age);
            printf("Name : %s, Age : %d", s2.name,s2.age);
        fclose(fptr);
    }
    return 0;
}