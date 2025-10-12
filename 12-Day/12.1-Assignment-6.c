//
// Created by phyo-aung-naing-tun on 10/12/25.
// Assignment 6
//


#include "stdio.h"
#include "stdlib.h"


/**
 * Functions Start .............................
 */
void menu();

void registration();

void login();

void save_data();

void sync_data();

/**
 * Functions End ...............................
 */

/**
 * Helpers Start .............................
 */
void copy_two_char_array(char target[50], char data[50]);

int check_two_char_array();

int get_char_array_count(char data[50]);

/**
 * Helpers End ...............................
 */
// .........................................................//

typedef struct {
    int id;
    int user_id;
    int related_id;
    int amount;
    int before_amount;
    int after_amount;
    char type[4]; //in or out
    char remark[50];
} POINT_TRANSACTION;

typedef struct {
    int id;
    char name[20];
    char email[20];
    int phone;
    int postcode;
    char address[50];
    int point;
    char role[10];
    POINT_TRANSACTION point_transaction[100];
} DB;

DB users[10];


/*
* global variables
*/
const int G_USER_INITIAL_POINT = 100;
const char G_USER_ROLE_USER[5] = "user";
const char G_USER_ROLE_ADMIN[6] = "admin";

int g_user_count = 0;
int g_available_user_count = 10;
int g_available_point_transaction_count = 100;
/*
 * global variables
 */

int main() {
    printf("****************Welcome To IDS System***************\n");
    sync_data();
    menu();
    return 0;
}

/**
* Functions Start .............................
*/
void menu() {
    int option = -1;
    printf("\nEnter 1 to Register\nEnter 2 to Login\nEnter 3 To Exit\n");
    printf("Enter Here => ");
    scanf("%d", &option);

    if (option == 1) {
        registration();
        menu();
    } else if (option == 2) {
        login();
    } else if (option == 3) {
        save_data();
        sync_data();
        exit(1);
    } else {
        printf("******Wrong Option*******\n");
        menu();
    }
}

void registration() {
    printf("*********Registration Form*********\n");

    char r_name[20];
    char r_email[20];
    int r_phone;
    int r_postcode;
    char r_address[50];

    printf("Enter User Name => ");
    scanf(" %[^\n]", &r_name[0]);

    printf("Enter User Email => ");
    scanf(" %[^\n]", &r_email[0]);

    printf("Enter User Phone => ");
    scanf("%d", &r_phone);

    printf("Enter User Postcode => ");
    scanf("%d", &r_postcode);

    printf("Enter User Address => ");
    scanf(" %[^\n]", &r_address[0]);

    users[g_user_count].id = g_user_count + 1;
    copy_two_char_array(users[g_user_count].name, r_name);
    copy_two_char_array(users[g_user_count].email, r_email);
    users[g_user_count].phone = r_phone;
    users[g_user_count].postcode = r_postcode;
    copy_two_char_array(users[g_user_count].address, r_address);
    copy_two_char_array(users[g_user_count].role, G_USER_ROLE_USER);
    users[g_user_count].point = G_USER_INITIAL_POINT;
    g_user_count++;

   printf("*********Registered Successfully*********\n");


   //  printf("\n*********Checking The Registration Data*********\n");
   //
   // for (int x = 0; x < g_user_count; x++) {
   //     printf("\nUser Id is => %d\n", users[x].id);
   //     printf("User Name is => %s\n", users[x].name);
   //     printf("User Email is => %s\n", users[x].email);
   //     printf("User Phone is => %d\n", users[x].phone);
   //     printf("User Postcode is => %d\n", users[x].postcode);
   //     printf("User Point is => %d\n", users[x].point);
   //     printf("User Address is => %s\n", users[x].address);
   //     printf("User Role is => %s\n", users[x].role);
   // }

};

void login() {
    printf("*********Login Form*********\n");
}

void save_data() {
    printf("*********Start Saving Data*********\n");
    FILE *fptr = fopen("database.bin","wb");

    if (!fptr) {
        perror("Save Data Error\n");
    }

    fwrite(users,sizeof(DB),g_user_count,fptr);

    fclose(fptr);
    printf("*********Saved Data Successfully*********\n");


}

void sync_data() {
    printf("*********Start Sync Data Form*********\n");

    FILE *fptr = fopen("database.bin","rb");
    if (!fptr) {
        perror("Save Data Error\n");
    }
    int index = 0;
    while ( fread(&users[index],sizeof(DB),1,fptr) == 1) {
        printf("=");
        // printf("\nUser Id is => %d\n", users[index].id);
        // printf("User Name is => %s\n", users[index].name);
        // printf("User Email is => %s\n", users[index].email);
        // printf("User Phone is => %d\n", users[index].phone);
        // printf("User Postcode is => %d\n", users[index].postcode);
        // printf("User Point is => %d\n", users[index].point);
        // printf("User Address is => %s\n", users[index].address);
        // printf("User Role is => %s\n", users[index].role);
        index++;
    }
    g_user_count = index;
    fclose(fptr);
    printf("\n*********Finish Sync Data Form*********\n");

}

/**
 * Functions End ...............................
 */

/**
 * Helpers Start .............................
 */


void copy_two_char_array(char target[50], char data[50]) {
    for (int x = 0; x < 50; x++) {
        if (data[x] == '\0') {
            break;
        }
        target[x] = data[x];
    }
}

int check_two_char_array(char target[50]) {
}

int get_char_array_count(char data[50]) {
    int size = 0;
    for (int x = 0; x < 50; x++) {
        if (data[x] == '\0') {
            break;
        }
        size++;
    }
    return size;
}

/**
 * Helpers End ...............................
 */
