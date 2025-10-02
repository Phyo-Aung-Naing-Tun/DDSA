//
// Created by phyo-aung-naing-tun on 9/15/25.
// Register, Login and Logout
//

#include <stdio.h>
#include <stdlib.h>

void menu();

void registration();

void login();

/**
 * Start Helper Functions
 */

void copy_two_char_array(char destination[50], char data[50]);

int check_two_char_array(char target[50], char data[50]);

/**
 * End Helper Functions
 */

/**
 * Start After Login
 */

void show_user_dashboard();

void see_user_infos();

void logout();

/**
 * End After Login
 */

struct Db {
    int id;
    char name[50];
    char email[50];
    char password[50];
    int phone;
};

struct Db users[5];

/**
 * Start Global Variables
 */

int g_menu_option = 0;
int g_user_count = 0;
int g_login_user_id = -1;
int g_login_tried_count = 0;
int g_max_allowed_login_tried_count = 3;

/**
 * End Global Variables
 */

int main() {
    menu();

    return 0;
}

void menu() {
    while (1) {
        printf("Intelligent Delivery System\n");
        printf("Enter 1 To Register\n");
        printf("Enter 2 To Login\n");
        printf("Enter 3 To Exit\n");
        printf("Enter Here ===> ");
        scanf("%d", &g_menu_option);

        if (g_menu_option == 1) {
            registration();
        } else if (g_menu_option == 2) {
            login();
        } else {
            printf("\n--------------------Bye Bye---------------\n");
            exit(0);
        }
    }
}

void registration() {
    printf("\n--------------------Registration Form---------------\n");
    char r_name[50];
    char r_email[50];
    char r_password[50];
    int r_phone;

    printf("Enter Your Name => ");
    scanf(" %[^\n]", &r_name[0]);
    printf("Enter Your Email => ");
    scanf(" %[^\n]", &r_email[0]);
    printf("Enter Your Password => ");
    scanf(" %[^\n]", &r_password[0]);
    printf("Enter Your Phone => ");
    scanf("%d", &r_phone);

    users[g_user_count].id = g_user_count;
    printf("\nChecking User Id %d\n", users[g_user_count].id);

    copy_two_char_array(users[g_user_count].name, r_name);
    printf("Checking User Name %s\n", users[g_user_count].name);

    copy_two_char_array(users[g_user_count].email, r_email);
    printf("Checking User Email %s\n", users[g_user_count].email);

    copy_two_char_array(users[g_user_count].password, r_password);
    printf("Checking User Password %s\n", users[g_user_count].password);

    users[g_user_count].phone = r_phone;
    printf("Checking User Phone %d\n", users[g_user_count].phone);

    g_user_count++;
    printf("\n**** Successfully Registered ****\n");
}

void login() {
    printf("\n--------------------Login Form---------------\n");
    char l_email[50];
    char l_password[50];

    printf("Enter Your Email => ");
    scanf(" %[^\n]", &l_email[0]);
    printf("Enter Your Password => ");
    scanf(" %[^\n]", &l_password[0]);

    for (int x = 0; x < g_user_count; x++) {
        int checked_email_result = check_two_char_array(users[x].email, l_email);
        if (checked_email_result == 1) {
            int checked_password_result = check_two_char_array(users[x].password, l_password);
            if (checked_password_result == 1) {
                g_login_user_id = users[x].id;
                break;
            }
        }
    }

    if (g_login_user_id > -1) {
        g_login_tried_count = 0;
        printf("\n**** Successfully Login ****\n");
        show_user_dashboard();
    } else {
        if (g_login_tried_count < g_max_allowed_login_tried_count) {
            printf("\n**** Your Information Do Not Match. Please Type Again! ****\n");
            g_login_tried_count++;
            menu();
        } else if (g_login_tried_count == g_max_allowed_login_tried_count) {
            printf("\n**** Your Information Do Not Match. Please Type Again! ****\n");
            printf("\n**** This Is Your Last Chance ****\n");
            g_login_tried_count++;
            menu();
        } else {
            exit(0);
        }
    }
}

/**
 * Start After Authenticated
 */
void show_user_dashboard() {
    int user_option = 0;
    printf("********* Welcome %s ********\n", users[g_login_user_id].name);
    printf("Enter 1 To See Your Informations\n");
    printf("Enter 2 To Logout\n");
    printf("Enter Others To Exist Program\n");

    scanf("%d", &user_option);

    if (user_option == 1) {
        see_user_infos();
    } else if (user_option == 2) {
        logout();
    } else {
        exit(0);
    }
}


void see_user_infos() {
    int go_back = 0;
    printf("Here Your Information's\n");
    printf("%s\n", users[g_login_user_id].name);
    printf("%s\n", users[g_login_user_id].email);
    printf("%d\n", users[g_login_user_id].phone);

    printf("Enter 1 to go back ===> ");
    scanf("%d", &go_back);
    if (go_back == 1) {
        show_user_dashboard();
    } else {
        scanf("%d", &go_back);
    }
}

void logout() {
    g_login_user_id = -1;
    g_login_tried_count = 0;
    menu();
}

/**
 * End After Authenticated
 */

/**
 * Start Helper Functions
 */
void copy_two_char_array(char destination[50], char data[50]) {
    for (int x = 0; x < 50; x++) {
        if (data[x] == "\0") {
            break;
        }
        destination[x] = data[x];
    }
}

int check_two_char_array(char target[50], char data[50]) {
    int is_same = 0;
    for (int x = 0; x < 50; x++) {
        if (data[x] == '\0') {
            break;
        }
        if (target[x] == data[x]) {
            is_same = 1;
        } else {
            is_same = 0;
            break;
        }
    }
    return is_same;
}

/**
 * End Helper Functions
 */
