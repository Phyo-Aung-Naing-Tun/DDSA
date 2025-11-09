//
// Created by phyo-aung-naing-tun on 11/4/25.
// Link List
//

#include "stdio.h"

struct Node {
    int data;
    struct Node* next;
};

int main() {

    struct Node* head = NULL;
    struct Node* one = NULL;
    struct Node* two = NULL;
    struct Node* three = NULL;

    head = (struct Node*)malloc(sizeof(struct Node));
    one = (struct Node*)malloc(sizeof(struct Node));
    two = (struct Node*)malloc(sizeof(struct Node));
    three = (struct Node*)malloc(sizeof(struct Node));

    head->data = 1;
    head->next = one;
    one->data = 2;
    one->next = two;
    two->data = 3;
    two->next = three;
    three->data = 4;
    three->next = NULL;

    return 0;
}
