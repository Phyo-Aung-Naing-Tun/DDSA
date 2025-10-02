//
// Created by phyo-aung-naing-tun on 9/2/25.
// Structure and Logics
//

#include <stdlib.h>
#include "stdio.h"

struct Db {
    char username[20];
    char email[20];
    char password[20];
};

struct Db users[10];

int g_count = 0;
int pass_index = -1;

void menu();

void register_user();

void copy_character_array(char destination[20], char userData[20]);

void login();

int check_character_array(char first[20], char second[20]);

int main() {
    printf("Welcome To Our System\n");
    while (1) {
        menu();
    }
    return 0;
}

void menu() {
    int number = 0;
    printf("Enter 1 To Register\n");
    printf("Enter 2 To Login\n");
    printf("Enter 3 To Out\n");
    printf("Enter : ");
    scanf("%d", &number);

    if (number == 1) {
        printf("\nPlease Register Here");
        register_user();
    } else if (number == 2) {
        printf("\nPlease Login Here");
        login();
        if (pass_index > -1) {
            printf("\nLogin Successfully\n");
            printf("Username : %s\n", users[pass_index].username);
            printf("Email : %s\n", users[pass_index].email);
            printf("Password : %s\n", users[pass_index].password);
        }else {
            printf("\nPlease Login Failed\n");
        }

    } else if (number == 3) {
        exit(0);
    }
}

void login() {
    char l_email[20];
    char l_password[20];

    printf("Please Enter Email: ");
    scanf(" %[^\n]", &l_email[0]);
    printf("Please Enter Password: ");
    scanf(" %[^\n]", &l_password[0]);

    for (int i = 0; i < g_count; i++) {
        int first = check_character_array(l_email, users[i].email);
        if (first == 1) {
            int second = check_character_array(l_password, users[i].password);
            if (second == 1) {
                pass_index = i;
                break;
            }
        }
    }

}

void register_user() {
    char r_username[20];
    char r_email[20];
    char r_password[20];

    printf("Enter Username : ");
    scanf(" %[^\n]", &r_username[0]);
    printf("Enter Email : ");
    scanf(" %[^\n]", &r_email[0]);
    printf("Enter Password : ");
    scanf(" %[^\n]", &r_password[0]);

    copy_character_array(users[g_count].username, r_username);
    copy_character_array(users[g_count].email, r_email);
    copy_character_array(users[g_count].password, r_password);

    printf("Username is: %s\n", users[g_count].username);
    printf("Email is: %s\n", users[g_count].email);
    printf("Password is: %s\n", users[g_count].password);

    g_count++;
}

void copy_character_array(char destination[20], char userData[20]) {
    for (int i = 0; i < 20; i++) {
        if (userData[i] == "/0") {
            break;
        }
        destination[i] = userData[i];
    };
}

int check_character_array(char first[20], char second[20]) {
    int result = 1;
    for (int i = 0; i < 20; i++) {
        if (first[i] != second[i]) {
            result = 0;
            break;
        }
    }

    return result;
}
