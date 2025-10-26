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

void show_dashboard();

void user_dashboard(int login_user_index);

void admin_dashboard(int login_user_index);

void show_user_info(int login_user_index);

int confirm_password(int login_user_index);

void edit_user_info(int login_user_index);

int transfer_point(int login_user_index);


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

int get_auth_user_index();

int get_user_index_by_email();

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
    char status[10];
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
const char G_STATUS_ACTIVE[7] = "active";
const char G_STATUS_INACTIVE[10] = "inactive";

int g_user_count = 0;
int g_login_user_id = 0;
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
        printf(
            "Password Must Include at least One Small Letter\nOne Capital Letter\nOne Special Character and\nMust Be at least 6 Characters Long\nEnter User Password => ");
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
    copy_two_char_array(users[g_user_count].status, G_STATUS_ACTIVE);
    g_user_count++;

    printf("*********Registered Successfully*********\n");
};

void login() {
    printf("*********Login Form*********\n");
    char l_email[20];
    char l_password[20];
    int is_success = 0;


    printf("Enter Your Email => ");
    scanf(" %[^\n]", &l_email[0]);

    printf("Enter Your Password => ");
    scanf(" %[^\n]", &l_password[0]);

    for (int x = 0; x < g_user_count; x++) {
        int is_email_exist = check_two_char_array(users[x].email, l_email);
        if (is_email_exist) {
            int is_password_exist = check_two_char_array(users[x].password, l_password);
            if (is_password_exist) {
                g_login_user_id = users[x].id;
                is_success = 1;
                break;
            }
        }
    }

    if (is_success) {
        show_dashboard();
    } else {
        printf("Login Failed!\n");
        menu();
    }
}

void save_data() {
    printf("*********Start Saving Data*********\n");
    FILE *fptr = fopen("database.bin", "wb");

    if (!fptr) {
        perror("Save Data Error\n");
    }

    // char a_name[20] = "PhyoAungNaingTun";
    // char a_email[20] = "phyoaung@gmail.com";
    // char a_password[20] = "admin@123";
    // int a_phone = 111111;
    // char a_address[20] = "Hlaing";
    //
    //
    // users[g_user_count].id = g_user_count + 1;
    // copy_two_char_array(users[g_user_count].name, a_name);
    // copy_two_char_array(users[g_user_count].email, a_email);
    // copy_two_char_array(users[g_user_count].password, a_password);
    // users[g_user_count].phone = a_phone;
    // copy_two_char_array(users[g_user_count].address, a_address);
    // copy_two_char_array(users[g_user_count].role, G_USER_ROLE_ADMIN);
    // copy_two_char_array(users[g_user_count].status, G_STATUS_ACTIVE);
    // g_user_count++;

    fwrite(users, sizeof(DB), g_user_count, fptr);

    fclose(fptr);
    printf("*********Saved Data Successfully*********\n");
}

void sync_data() {
    printf("*********Start Sync Data Form*********\n");

    FILE *fptr = fopen("database.bin", "rb");
    if (!fptr) {
        perror("Save Data Error\n");
    }
    int index = 0;
    while (fread(&users[index], sizeof(DB), 1, fptr) == 1) {
        printf("\nUser Id is => %d\n", users[index].id);
        printf("User Name is => %s\n", users[index].name);
        printf("User Email is => %s\n", users[index].email);
        printf("User Phone is => %d\n", users[index].phone);
        printf("User Postcode is => %d\n", users[index].postcode);
        printf("User Point is => %d\n", users[index].point);
        printf("User Address is => %s\n", users[index].address);
        printf("User Status is => %s\n", users[index].status);
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
        printf("\nPhone Number (%d) has been used!\n", phone);
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

    char gmail_symbol[11] = {'@', 'g', 'm', 'a', 'i', 'l', '.', 'c', 'o', 'm'};
    char apple_mail_symbol[11] = {'@', 'a', 'p', 'p', 'l', 'e', '.', 'c', 'o', 'm'};
    char yahoo_mail_symbol[11] = {'@', 'y', 'a', 'h', 'o', 'o', '.', 'c', 'o', 'm'};
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
    int is_valid_yahoo_mail_symbol = check_two_char_array(yahoo_mail_symbol, second_part);
    int is_valid_apple_mail_symbol = check_two_char_array(apple_mail_symbol, second_part);

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
        } else if (is_small_letter(password[x])) {
            is_include_small_letter = 1;
        } else if (is_capital_letter(password[x])) {
            is_include_capital_letter = 1;
        } else if (is_special_character(password[x])) {
            is_include_special_character = 1;
        }
    }

    if (is_include_number && is_include_capital_letter && is_include_small_letter && is_include_special_character) {
        return 1;
    }

    printf("\nInvalid Password\n");
    return 0;
}


void show_dashboard() {
    printf("\n****Welcome To IDS Delivery ****\n");
    int user_index = get_auth_user_index();
    if (check_two_char_array(G_USER_ROLE_USER, users[user_index].role)) {
        user_dashboard(user_index);
    } else {
        admin_dashboard(user_index);
    }
}

void user_dashboard(int login_user_index) {
    printf("\n Welcome User (%s) \n", users[login_user_index].name);
    int option = 0;
    printf("Enter 1 To See Your Info. Enter 2 To Edit Your Info.\nEnter 3 To Transfer Points. Enter 4 To Logout\n");
    printf("Enter Here => ");
    scanf("%d", &option);
    switch (option) {
        case 1:
            printf("********* User Info ********\n");
            show_user_info(login_user_index);
            user_dashboard(login_user_index);
            break;
        case 2:
            printf("********* Edit Your Info ******\n");
            edit_user_info(login_user_index);
            break;
        case 3:
            transfer_point(login_user_index);
            break;
        case 4:
            printf("********** Bye Bye **********\n");
            menu();
            break;
        default:
            printf("******** Wrong Choice! *********\n");
            user_dashboard(login_user_index);
    }
}

void admin_dashboard(int login_user_index) {
    printf("\n Welcome Admin (%s) \n", users[login_user_index].name);
    int option = 0;
    printf("Enter 1 To See Your Info. Enter 2 To Edit Your Info.\nEnter 3 To Manage Users. Enter 4 To Logout\n");
    printf("Enter Here => ");
    scanf("%d", &option);

    switch (option) {
        case 1:
            printf("********* User Info ********\n");
            show_user_info(login_user_index);
            admin_dashboard(login_user_index);
            break;
        case 2:
            printf("********* Edit Your Info ******\n");
            edit_user_info(login_user_index);
            break;
        case 3:
            printf("********* Manage Users *******\n");
            break;
        case 4:
            printf("********** Bye Bye **********\n");
            menu();
            break;
        default:
            printf("******** Wrong Choice! *********\n");
            admin_dashboard(login_user_index);
    }
}

void show_user_info(int login_user_index) {
    printf("Your Name is     %s.\n", users[login_user_index].name);
    printf("Your Email is    %s.\n", users[login_user_index].email);
    printf("Your Point is    %d.\n ", users[login_user_index].point);
    printf("Your Role is     %s.\n ", users[login_user_index].role);
    printf("Your Phone is    %d.\n ", users[login_user_index].phone);
    printf("Your Postcode is %d.\n ", users[login_user_index].postcode);
    printf("Your address is  %s.\n ", users[login_user_index].address);
}

void edit_user_info(int login_user_index) {
    int e_option = 0;
    int is_valid_email = 0;
    int is_valid_phone = 0;
    int is_valid_password = 0;
    char e_password[20];
    char e_name[20];
    char e_email[20];
    int e_phone;
    int e_postcode;
    char e_address[50];

    printf(
        "Enter 1 To Edit Name\nEnter 2 To Email\nEnter 3 To Edit Phone\nEnter 4 To Edit Postcode\nEnter 5 To Edit Address\nEnter 6 To Change Password => ");
    scanf("%d", &e_option);

    if (e_option == 1) {
        printf("Enter User Name => ");
        scanf(" %[^\n]", &e_name[0]);
        copy_two_char_array(users[login_user_index].name, e_name);
        printf("\n Updated User Name Successfully and New User Name is (%s).\n", users[login_user_index].name);
    } else if (e_option == 2) {
        while (!is_valid_email) {
            printf("Enter User Email => ");
            scanf(" %[^\n]", &e_email[0]);
            is_valid_email = validate_email(e_email);
        }
        copy_two_char_array(users[login_user_index].email, e_email);
        printf("\n Updated User Email Successfully and New User Email is (%s).\n", users[login_user_index].email);
    } else if (e_option == 3) {
        while (!is_valid_phone) {
            printf("Enter User Phone => ");
            scanf("%d", &e_phone);
            is_valid_phone = validate_phone(e_phone);
        }
        users[login_user_index].phone = e_phone;
        printf("\n Updated User Phone Successfully and New User Phone is (%d).\n", users[login_user_index].phone);
    } else if (e_option == 4) {
        printf("Enter User Postcode => ");
        scanf("%d", &e_postcode);
        users[login_user_index].postcode = e_postcode;
        printf("\n Updated User Postcode Successfully and New User Postcode is (%d).\n",
               users[login_user_index].postcode);
    } else if (e_option == 5) {
        printf("Enter User Address => ");
        scanf(" %[^\n]", &e_address[0]);

        copy_two_char_array(users[login_user_index].address, e_address);
        printf("\n Updated User Address Successfully and New User Address is (%s).\n", users[login_user_index].address);
    } else if (e_option == 6) {
        if (!confirm_password(login_user_index)) {
            int option = 0;
            printf("Password Confirmation is invalid!\nEnter 1 To Retry\nEnter Other To Stop\n");
            printf("Enter Here => ");
            scanf("%d", &option);
            if (option == 1) {
                edit_user_info(login_user_index);
            } else {
                show_dashboard();
            }
        }
        while (!is_valid_password) {
            printf(
                "Password Must Include at least One Small Letter\nOne Capital Letter\nOne Special Character and\nMust Be at least 6 Characters Long\nEnter User Password => ");
            scanf(" %[^\n]", &e_password[0]);
            is_valid_password = validate_password(e_password);
        }
        copy_two_char_array(users[login_user_index].password, e_password);
        printf("\n Updated User Password Successfully and New Password is (%s).\n", users[login_user_index].password);
    } else {
        printf("\n***** Wrong Option ******\n");
        edit_user_info(login_user_index);
    }

    printf("\nEnter 1 to continue or 2 to go back=> ");
    scanf("%d", &e_option);
    if (e_option == 1) {
        edit_user_info(login_user_index);
    } else {
        show_dashboard();
    }
}

int confirm_password(int login_user_index) {
    char c_password[20];
    printf("\n Confirm Your Password => ");
    scanf(" %[^\n]", &c_password[0]);
    if (check_two_char_array(users[login_user_index].password, c_password)) {
        return 1;
    }
    return 0;
}

int transfer_point(int login_user_index) {

    int remaining_point = users[login_user_index].point;
    printf("\n********* Transfer Your Point *******\n");
    printf("Your Remaining Points => %d\n", remaining_point);
    printf("-----------------------------------\n");

    printf("********** Enter Receiver Email ***********\n");
    int receiver_index = get_user_index_by_email();

    if (receiver_index == -1 || check_two_char_array(G_USER_ROLE_ADMIN, users[receiver_index].role)) {
        printf("********** Receiver Not Found! Please Try Again **********\n");
        transfer_point(login_user_index);
    }

    printf("\n********** Receiver Info ***********\n");
    printf("Name => %s\n", users[receiver_index].name);
    printf("Phone => %d\n", users[receiver_index].phone);
    printf("Email => %s\n", users[receiver_index].email);
    printf("-------------------------------------------------\n");

    int enough_point = 0;
    int amount = 0;
    while (!enough_point) {
        printf("Enter Amount => ");
        scanf("%d", &amount);
        if (amount < remaining_point) {
            enough_point = 1;
        }else {
            printf("*********** You Don't Have Enough Point!************\n");
        }
    }

    users[receiver_index].point = users[receiver_index].point + amount;
    users[login_user_index].point = remaining_point - amount;


    printf("****************** Transfered Point Successfully ***************\n");

}

/**
 * Functions End ...............................
 */

/**
 * Helpers Start .............................
 */

int check_phone_duplication(int phone) {
    for (int x = 0; x < g_user_count; x++) {
        if (users[x].phone == phone) {
            return 1;
        }
    }
    return 0;
}

int check_email_duplication(char email[50]) {
    for (int x = 0; x < g_user_count; x++) {
        int is_same = check_two_char_array(users[x].email, email);
        if (is_same) {
            return 1;
        }
    }
    return 0;
}


void copy_two_char_array(char target[50], char data[50]) {
    for (int x = 0; x < 50; x++) {
        if (target[x] == '\0') {
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
    if ((data >= 32 && data <= 47) || (data >= 58 && data <= 64) || (data >= 91 && data <= 96) || (
            data >= 123 && data <= 126)) {
        return 1;
    }
    return 0;
}

int get_auth_user_index() {
    int login_user_index = -1;
    for (int x = 0; x < g_user_count; x++) {
        if (users[x].id == g_login_user_id) {
            login_user_index = x;
            break;
        }
    }
    return login_user_index;
}

int get_user_index_by_email() {
    char email[20];
    int user_index = -1;
    printf("Enter Email => ");
    scanf(" %[^\n]", &email[0]);

    for (int x = 0; x < g_user_count; x++) {
        if (check_two_char_array(users[x].email, email)) {
            user_index = x;
            break;
        }
    }

    return user_index;
}

/**
 * Helpers End ...............................
 */
