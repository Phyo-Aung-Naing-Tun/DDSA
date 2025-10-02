//
// Created by phyo-aung-naing-tun on 9/2/25.
// Structure and Logics
//

#include "stdio.h"

void registerUser(int index);
void copyData(char destination[50], char second[50]);

struct Dbb {
    char name[50];
    char email[50];
    char password[50];
    int phone;
};

struct Dbb data[3];

int main() {
    printf("Make User Registration\n");

    for (int i = 0; i < 3; i++) {
        registerUser(i);
    }

    for (int i = 0; i < 3; i++) {
        printf("Name => %s \n", data[i].name);
        printf("Email => %s \n", data[i].email);
        printf("Password => %s \n", data[i].password);
        printf("Phone number => %d \n\n", data[i].phone);
    }

    return 0;
}

void registerUser(int index)
{
    char r_name[50];
    char r_email[50];
    char r_password[50];
    int r_phone = 0;

    printf("Enter name :");
    scanf(" %[^\n]", &r_name[0]);

    printf("Enter email :");
    scanf(" %[^\n]", &r_email[0]);

    printf("Enter password :");
    scanf(" %[^\n]", &r_password[0]);

    printf("Enter phone number :");
    scanf("%d", &r_phone);

    copyData(data[index].name,r_name);
    copyData(data[index].email,r_email);
    copyData(data[index].password,r_password);
    data[index].phone = r_phone;

}

void copyData(char destination[50], char second[50]) {

    for (int i = 0; i < 50; i++) {
        if (second[i] != "\0") {
            destination[i] = second[i];
        }else {
            break;
        }

    }
}
