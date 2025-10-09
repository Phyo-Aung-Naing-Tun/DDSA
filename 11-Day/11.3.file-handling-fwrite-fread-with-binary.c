//
// Created by phyo-aung-naing-tun on 10/9/25.
// fwrite and fread

#include "stdio.h"
#include "stdlib.h"

typedef struct Student {
    char name[10];
    int age;
}Student;

int main() {

    Student s1 = {"aung aung",20};
    Student s2;

    FILE *fptr;

    fptr = fopen("test.bin","wb");
    if (fptr == NULL) {
        perror("\n");
    }else {
        fwrite(&s1,sizeof(Student),1,fptr);
        fclose(fptr);
    }

    fptr = fopen("test.bin","rb");
    if (fptr == NULL) {
        perror("\n");
    }else {
        fread(&s2,sizeof(Student),1,fptr);
        fclose(fptr);
    }

    printf("Name is %s and age is %d",s2.name,s2.age);

    return 0;

}