//
// Created by phyo-aung-naing-tun on 9/1/25.
// Assignment 2
//

#include "stdio.h"

int getTotalMark(int studentMarks[6]);
int isPass(int studentMarks[6]);
int getDestination(int studentMarks[6]);

int main() {

    int mgmgMark[6] = {50, 60, 70, 40, 30, 80};
    int kokoMark[6] = {80, 60, 70, 40, 90, 80};
    int susuMark[6] = {40, 40, 40, 40, 40, 40};

    printf("Mg Mg's total marks is : %d\n", getTotalMark(mgmgMark));
    if (isPass(mgmgMark)) {
        printf("Mg Mg Pass\n");
        if (getDestination(mgmgMark)) {
            printf("Mg Mg Get Destination\n");
        }
    }else {
        printf("Mg Mg Fail\n");
    }
    printf("\n");

    printf("Ko Ko's total marks is : %d\n", getTotalMark(kokoMark));
    if (isPass(kokoMark)) {
        printf("Ko Ko Pass\n");
        if (getDestination(kokoMark)) {
            printf("Ko Ko Get Destination\n");
        }
    }else {
        printf("Ko Ko Fail\n");
    }
    printf("\n");


    printf("Su Su's total marks is : %d\n", getTotalMark(susuMark));
    if (isPass(susuMark)) {
        printf("Su Su Pass\n");
        if (getDestination(susuMark)) {
            printf("Su Su Get Destination\n");
        }
    }else {
        printf("Su Su Fail\n");
    }
    printf("\n");


    return 0;
}

int getTotalMark(int studentMarks[6]) {
    int totalMark = 0;
    for (int x = 0; x < 6; x++) {
        totalMark += studentMarks[x];
    }
    return totalMark;
}

int isPass(int studentMarks[6]) {
    int isPass = 1;
    int minMark = 40;
    for (int x = 0; x < 6; x++) {
        if (studentMarks[x] < minMark) {
            isPass = 0;
        }
    }
    return isPass;
}

int getDestination(int studentMarks[6]) {
    int destination = 0;
    int minDestinationMark = 80;
    for (int x = 0; x < 6; x++) {
        if (studentMarks[x] >= minDestinationMark) {
            destination = 1;
        }
    }
    return destination;
}