//
// Created by phyo-aung-naing-tun on 10/8/25.
//

#include "stdio.h"
#include "stdlib.h"

int main() {

    FILE *fptr;
    fptr = fopen("test.txt","w");

    if (fptr == NULL) {
        perror("File Open Error:\n");
        return -1;
    } else {
        printf("File Opened Successfully\n");
        char text[11] = {'h','e','l','l','o',' ','w','o','r','l','d'};

        for (int x = 0; x < 11; x++) {
            fputc(text[x],fptr);
        }
        fclose(fptr);
    }

    fptr = fopen("test.txt","a");
    if (fptr == NULL) {
        perror("File Open Error:\n");
        return -1;
    } else {
        printf("File Opened Successfully\n");

        fputs("\nThis is Testing!\n",fptr);

        fclose(fptr);
    }

    fptr = fopen("test.txt","r");
    if (fptr == NULL) {
        perror("File Open Error:\n");
        return -1;
    } else {
        int c;
        while ((c = fgetc(fptr)) != EOF) {
            printf("%c", c);
        }
        fclose(fptr);
    }


    return 0;
}