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

int validate_phone(int phone);

int validate_email(char email[50]);

int validate_password(char password[20]);

/**
 * Functions End ...............................
 */

/**
 * Helpers Start .............................
 */
int check_phone_duplication(int phone);

int check_email_duplication(char email[50]);

void copy_two_char_array(char target[50], char data[50]);

int check_two_char_array(char target[50], char data[50]);

int get_char_array_count(char data[50]);

int is_number(char data);

int is_small_letter(char data);

int is_capital_letter(char data);

int is_special_character(char data);

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
    char password[20];
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

    int is_valid_email = 0;
    int is_valid_phone = 0;
    int is_valid_password = 0;
    char r_password[20];
    char r_name[20];
    char r_email[20];
    int r_phone;
    int r_postcode;
    char r_address[50];

    printf("Enter User Name => ");
    scanf(" %[^\n]", &r_name[0]);

    while (!is_valid_email) {
        printf("Enter User Email => ");
        scanf(" %[^\n]", &r_email[0]);
        is_valid_email = validate_email(r_email);
    }

    while (!is_valid_phone) {
        printf("Enter User Phone => ");
        scanf("%d", &r_phone);
        is_valid_phone = validate_phone(r_phone);
    }

    while (!is_valid_password) {
        printf("Password Must Include at least One Small Letter\nOne Capital Letter\nOne Special Character and\nMust Be at least 6 Characters Long\nEnter User Password => ");
        scanf(" %[^\n]", &r_password[0]);
        is_valid_password = validate_password(r_password);
    }

    printf("Enter User Postcode => ");
    scanf("%d", &r_postcode);

    printf("Enter User Address => ");
    scanf(" %[^\n]", &r_address[0]);

    users[g_user_count].id = g_user_count + 1;
    copy_two_char_array(users[g_user_count].name, r_name);
    copy_two_char_array(users[g_user_count].email, r_email);
    copy_two_char_array(users[g_user_count].password, r_password);
    users[g_user_count].phone = r_phone;
    users[g_user_count].postcode = r_postcode;
    copy_two_char_array(users[g_user_count].address, r_address);
    copy_two_char_array(users[g_user_count].role, G_USER_ROLE_USER);
    users[g_user_count].point = G_USER_INITIAL_POINT;
    g_user_count++;

   printf("*********Registered Successfully*********\n");

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
        printf("\nUser Id is => %d\n", users[index].id);
        printf("User Name is => %s\n", users[index].name);
        printf("User Email is => %s\n", users[index].email);
        printf("User Phone is => %d\n", users[index].phone);
        printf("User Postcode is => %d\n", users[index].postcode);
        printf("User Point is => %d\n", users[index].point);
        printf("User Address is => %s\n", users[index].address);
        printf("User Role is => %s\n", users[index].role);
        index++;
    }
    g_user_count = index;
    fclose(fptr);
    printf("\n*********Finish Sync Data Form*********\n");

}

int validate_phone(int phone) {

    int is_phone_duplicate = check_phone_duplication(phone);

    if (is_phone_duplicate) {
        printf("\nPhone Number (%d) has been used!\n",phone);
        return 0;
    }
    return 1;
}


/**
 *  must be small letters
 *  must not include special characters and spaces
 *  numbers - 48 to 57
 *  small letters - 97 to 122
 *  must end with (@gmail.com,@apple.com,@yahoo.com)
 *
 * @param email
 * @return int
 */
int validate_email(char email[50]) {
    int size_of_email = get_char_array_count(email);
    int is_email_duplicate = check_email_duplication(email);
    int second_part_start_index = 0;

    if (is_email_duplicate) {
        printf("\nEmail (%s) has been used!\n", email);
        return 0;
    }

    for (int x = 0; x < size_of_email; x++) {
        if (email[x] == '@') {
            second_part_start_index = x;
            break;
        }
        if (!(is_number(email[x]) || is_small_letter(email[x]))) {
            printf("\nEmail (%s) is invalid!\n", email);
            return 0;
        }
    }

    char gmail_symbol[11] = {'@','g','m','a','i','l','.','c','o','m'};
    char apple_mail_symbol[11] = {'@','a','p','p','l','e','.','c','o','m'};
    char yahoo_mail_symbol[11] = {'@','y','a','h','o','o','.','c','o','m'};
    char second_part[20];
    int index = 0;

    for (int x = second_part_start_index; x < size_of_email; x++) {
        if (email[x] == '\0') {
            break;
        }
        second_part[index] = email[x];
        index++;
    }

    int is_valid_gmail_symbol = check_two_char_array(gmail_symbol, second_part);
    int is_valid_yahoo_mail_symbol = check_two_char_array(yahoo_mail_symbol,second_part);
    int is_valid_apple_mail_symbol = check_two_char_array(apple_mail_symbol,second_part);

    if (!(is_valid_gmail_symbol || is_valid_yahoo_mail_symbol || is_valid_apple_mail_symbol)) {
        printf("\nEmail (%s) is invalid!\n", email);
        return 0;
    }
    return 1;
}

/***
 * min 6 char
 * must include at least one capital Letter
 * must include at least one number
 * must include at least one small letter
 * must include at least one special character
 */
int validate_password(char password[20]) {
    int is_include_number = 0;
    int is_include_capital_letter = 0;
    int is_include_small_letter = 0;
    int is_include_special_character = 0;
    int size_of_password = get_char_array_count(password);

    if (size_of_password < 6) {
        printf("\nInvalid Password\n");
        return 0;
    }

    for (int x = 0; x < size_of_password; x++) {
        if (is_number(password[x])) {
            is_include_number = 1;
        }else if (is_small_letter(password[x])) {
            is_include_small_letter = 1;
        }else if (is_capital_letter(password[x])) {
            is_include_capital_letter = 1;
        }else if (is_special_character(password[x])) {
            is_include_special_character = 1;
        }
    }

    if (is_include_number && is_include_capital_letter && is_include_small_letter && is_include_special_character) {
        return 1;
    }

    printf("\nInvalid Password\n");
    return 0;
}

/**
 * Functions End ...............................
 */

/**
 * Helpers Start .............................
 */

int check_phone_duplication(int phone) {
    for (int x = 0; x < g_user_count; x++) {
        if(users[x].phone == phone) {
            return 1;
        }
    }
    return 0;
}

int check_email_duplication(char email[50]) {
    for (int x = 0; x < g_user_count; x++) {
        int is_same = check_two_char_array(users[x].email,email);
        if(is_same) {
            return 1;
        }
    }
    return 0;
}


void copy_two_char_array(char target[50], char data[50]) {
    for (int x = 0; x < 50; x++) {
        if (data[x] == '\0') {
            break;
        }
        target[x] = data[x];
    }
}

int check_two_char_array(char target[50], char data[50]) {

    int targetCount = get_char_array_count(target);
    int dataCount = get_char_array_count(data);

    if (targetCount != dataCount) {
        return 0;
    }
    for (int x = 0; x < 50; x++) {
        if (target[x] == '\0') {
            break;
        }
        if (target[x] != data[x]) {
            return 0;
        }
    }
    return 1;
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

int is_number(char data) {
    if (data >= 48 && data <= 57) {
        return 1;
    }
    return 0;
}

int is_small_letter(char data) {
    if (data >= 97 && data <= 122) {
        return 1;
    }
    return 0;
}

int is_capital_letter(char data) {
    if (data >= 65 && data <= 90) {
        return 1;
    }
    return 0;
}

int is_special_character(char data) {
    if ((data >= 32 && data <= 47) || (data >= 58 && data <= 64) || (data >= 91 && data <= 96) || (data >= 123 && data <= 126)) {
        return 1;
    }
    return 0;
}

/**
 * Helpers End ...............................
 */
