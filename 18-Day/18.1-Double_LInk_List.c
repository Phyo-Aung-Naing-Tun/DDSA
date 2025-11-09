//
// Created by phyo-aung-naing-tun on 11/8/25.
//
#include "stdio.h"
#include "stdlib.h"

struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
};

struct Node *createNode(int newData) {
    struct Node* newNode = (struct Node *) malloc(sizeof(struct Node));
    newNode->data = newData;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void insertAtBeginning(struct Node** head, int newData) {
    struct Node* newNode = createNode(newData);
    if (*head != NULL) {
        (*head)->prev = newNode;
        newNode->next = *head;
    }
    *head = newNode;
}

void prepand(struct Node** head, int newData) {
    struct Node* newNode = createNode(newData);
    struct Node* temp = *head;

    if (*head == NULL) {
        *head = newNode;
    }else {
        while (temp->next != NULL){
            temp = temp->next;
        };

        temp->next = newNode;
        newNode->prev = temp;
    }
}

int main() {
    struct Node *header = NULL;
    prepand(&header, 20);
    prepand(&header, 30);
    prepand(&header, 40);
    insertAtBeginning(&header, 10);
    return 0;
}
