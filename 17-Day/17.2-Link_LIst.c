//
// Created by phyo-aung-naing-tun on 11/4/25.
// Link List
//

#include "stdio.h"
#include "stdlib.h"

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int newData) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = newData;
    newNode->next = NULL;
    return newNode;
}

void insertFront(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

void showAllData(struct Node* head) {
    while (head != NULL) {
        printf("data => %d\n", head->data);
        head = head->next;
    }
}

void deleteNode(struct Node** head, int data) {

    struct Node* temp = *head;
    struct Node* prev = NULL;
    while  (temp != NULL) {
        if (temp->data == data) {
            if (prev != NULL) {
                prev->next = temp->next;
                *head = prev;
                free(temp);
            }else {
              *head =  temp->next;
                free(temp);
            }
            break;
        }else {
            prev = temp;
        }
        temp = temp->next;
    }


}


int main() {

    struct Node* head = NULL;
    insertFront(&head, 100);
    insertFront(&head, 200);
    insertFront(&head, 300);
    insertFront(&head, 400);

    showAllData(head);
    deleteNode(&head, 200);
    printf("After Delete \n");
    showAllData(head);


    free(head);
    return 0;
}