//
// Created by phyo-aung-naing-tun on 10/29/25.
//

#ifndef DDSA_N1C_H
#define DDSA_N1C_H

#include "stdio.h"
#include "stdlib.h"
#include "n1chelpers.h"
#include "n1c_g_variables.h"
#include "time.h"


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

void transfer_point(int login_user_index);

void show_user_point_transaction(int login_user_index);

void manage_user(int login_user_index);

void show_users();

void bann_user(int login_user_index);

void active_user(int login_user_index);

int check_user_active(int user_index);

/**
* Functions Start .............................
*/
inline void menu() {
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
        exit(1);
    } else {
        printf("******Wrong Option*******\n");
        option = -1;
        menu();
    }
}

inline void registration() {
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
    users[g_user_count].point_transaction_count = 0;
    g_user_count++;

    printf("*********Registered Successfully*********\n");
};

inline void login() {
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
                if (check_user_active(x)) {
                    g_login_user_id = users[x].id;
                    is_success = 1;
                    break;
                }else {
                    printf("***************Your Account Is Banned By Admin*********\n");
                    break;
                }

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

inline void save_data() {
    printf("*********Start Saving Data*********\n");
    FILE *fptr = fopen("database_two.bin", "wb");

    if (!fptr) {
        perror("Save Data Error\n");
    }

    fwrite(users, sizeof(DB), g_user_count, fptr);

    fclose(fptr);
    printf("*********Saved Data Successfully*********\n");
}

inline void sync_data() {
    printf("*********Start Sync Data Form*********\n");

    FILE *fptr = fopen("database_two.bin", "rb");
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
    //add admin data in initial
    if (g_user_count == 0) {
        printf("*************Added Admin Data***********\n");
        char a_name[20] = "PhyoAungNaingTun";
        char a_email[20] = "admin@gmail.com";
        char a_password[20] = "admin@123";
        int a_phone = 111111;
        char a_address[20] = "Insein";

        users[g_user_count].id = g_user_count + 1;
        copy_two_char_array(users[g_user_count].name, a_name);
        copy_two_char_array(users[g_user_count].email, a_email);
        copy_two_char_array(users[g_user_count].password, a_password);
        users[g_user_count].phone = a_phone;
        copy_two_char_array(users[g_user_count].address, a_address);
        copy_two_char_array(users[g_user_count].role, G_USER_ROLE_ADMIN);
        copy_two_char_array(users[g_user_count].status, G_STATUS_ACTIVE);
        users[g_user_count].point = 1000;
        g_user_count++;
    }

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
inline int validate_email(char email[50]) {
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
inline int validate_password(char password[20]) {
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


inline void show_dashboard() {
    printf("\n****Welcome To IDS Delivery ****\n");
    int user_index = get_auth_user_index();
    if (check_two_char_array(G_USER_ROLE_USER, users[user_index].role)) {
        user_dashboard(user_index);
    } else {
        admin_dashboard(user_index);
    }
}

inline void user_dashboard(int login_user_index) {
    printf("\n Welcome User (%s) \n", users[login_user_index].name);
    int option = 0;
    printf("Enter 1 To See Your Info.\nEnter 2 To Edit Your Info.\nEnter 3 To Transfer Points.\nEnter 4 To See Transactions\nEnter 5 To Logout\n");
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
            show_user_point_transaction(login_user_index);
           user_dashboard(login_user_index);
            break;
        case 5:
            printf("********** Bye Bye **********\n");
            menu();
        default:
            printf("******** Wrong Choice! *********\n");
            user_dashboard(login_user_index);
    }
}

inline void admin_dashboard(int login_user_index) {
    printf("\n Welcome Admin (%s) \n", users[login_user_index].name);
    int option = 0;
    printf("Enter 1 To See Your Info.\nEnter 2 To Edit Your Info.\nEnter 3 To Manage Users.\nEnter 4 To Logout\n");
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
            manage_user(login_user_index);
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

inline void show_user_info(int login_user_index) {
    printf("Your Name is     %s.\n", users[login_user_index].name);
    printf("Your Email is    %s.\n", users[login_user_index].email);
    printf("Your Point is    %d.\n ", users[login_user_index].point);
    printf("Your Role is     %s.\n ", users[login_user_index].role);
    printf("Your Phone is    %d.\n ", users[login_user_index].phone);
    printf("Your Postcode is %d.\n ", users[login_user_index].postcode);
    printf("Your address is  %s.\n ", users[login_user_index].address);
}

inline void edit_user_info(int login_user_index) {
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

inline int confirm_password(int login_user_index) {
    char c_password[20];
    printf("\n Confirm Your Password => ");
    scanf(" %[^\n]", &c_password[0]);
    if (check_two_char_array(users[login_user_index].password, c_password)) {
        return 1;
    }
    return 0;
}

inline void transfer_point(int login_user_index) {
    int option = -1;
    int remaining_point = users[login_user_index].point;
    printf("\n********* Transfer Your Point *******\n");
    printf("Your Remaining Points => %d\n", remaining_point);
    printf("-----------------------------------\n");

    printf("********** Enter Receiver Email ***********\n");
    int receiver_index = get_user_index_by_email();

    if (receiver_index == -1 || check_two_char_array(G_USER_ROLE_ADMIN, users[receiver_index].role)) {
        printf("********** Receiver Not Found! Please Try Again **********\n");
        printf("Enter 1 to go Back\nEnter 2 to continue\n");
        printf("Enter Here => ");
        scanf("%d", &option);
        if (option == 1) {
            show_dashboard();
        }else {
            transfer_point(login_user_index);
        }
    }

    if (receiver_index == login_user_index) {
        printf("********** You Can't Transfer Yourself! Please Try Again **********\n");
        printf("Enter 1 to go Back\nEnter 2 to continue\n");
        printf("Enter Here => ");
        scanf("%d", &option);
        if (option == 1) {
            show_dashboard();
        }else {
            transfer_point(login_user_index);
        }
    }

    if (!check_user_active(receiver_index)) {
        printf("********** Receiver Account Is Banned By Admin **********\n");
        printf("Enter 1 to go Back\nEnter 2 to continue\n");
        printf("Enter Here => ");
        scanf("%d", &option);
        if (option == 1) {
            show_dashboard();
        }else {
            transfer_point(login_user_index);
        }
    }

    printf("\n********** Receiver Info ***********\n");
    printf("Name => %s\n", users[receiver_index].name);
    printf("Phone => %d\n", users[receiver_index].phone);
    printf("Email => %s\n", users[receiver_index].email);
    printf("-------------------------------------------------\n");

    int confirm_option = 0;
    printf("Enter 1 To Continue\nEnter 2 To Go Back\nEnter 3 To Search Receiver\n");
    printf("Enter Here => ");
    scanf("%d", &confirm_option);

    if (confirm_option == 2) {
        show_dashboard();
    } else if (confirm_option == 3) {
        transfer_point(login_user_index);
    } else if (confirm_option == 1) {
        int enough_point = 0;
        int amount = 0;
        char remark[50];
        while (!enough_point) {
            printf("Enter Amount => ");
            scanf("%d", &amount);
            if (amount < remaining_point) {
                enough_point = 1;
            } else {
                printf("*********** You Don't Have Enough Point!************\n");
            }
        }
        printf("Enter Remark =>");
        scanf(" %[^\n]", &remark[0]);

        int receiver_transaction_count = users[receiver_index].point_transaction_count;
        int sender_transaction_count = users[login_user_index].point_transaction_count;

        //record receiver transaction
        users[receiver_index].point_transaction[receiver_transaction_count].id = receiver_transaction_count + 1;
        users[receiver_index].point_transaction[receiver_transaction_count].related_id = users[login_user_index].id;
        users[receiver_index].point_transaction[receiver_transaction_count].amount = amount;
        users[receiver_index].point_transaction[receiver_transaction_count].before_amount = users[receiver_index].point;
        users[receiver_index].point_transaction[receiver_transaction_count].after_amount =
                users[receiver_index].point + amount;
        copy_two_char_array(users[receiver_index].point_transaction[receiver_transaction_count].type, G_IN);
        set_now(users[receiver_index].point_transaction[receiver_transaction_count].transfer_at);
        copy_two_char_array(users[receiver_index].point_transaction[receiver_transaction_count].remark, remark);


        users[receiver_index].point_transaction_count = receiver_transaction_count + 1;

        //record sender transaction
        users[login_user_index].point_transaction[sender_transaction_count].id = sender_transaction_count + 1;
        users[login_user_index].point_transaction[sender_transaction_count].related_id = users[receiver_index].id;
        users[login_user_index].point_transaction[sender_transaction_count].amount = amount;
        users[login_user_index].point_transaction[sender_transaction_count].before_amount = users[login_user_index].
                point;
        users[login_user_index].point_transaction[sender_transaction_count].after_amount =
                users[login_user_index].point - amount;
        copy_two_char_array(users[login_user_index].point_transaction[sender_transaction_count].type, G_OUT);
        copy_two_char_array(users[login_user_index].point_transaction[sender_transaction_count].remark, remark);
        set_now(users[login_user_index].point_transaction[sender_transaction_count].transfer_at);
        users[login_user_index].point_transaction_count = sender_transaction_count + 1;


        users[receiver_index].point = users[receiver_index].point + amount;
        users[login_user_index].point = remaining_point - amount;

        printf("****************** Transfered Point Successfully ***************\n");
        show_dashboard();
    } else {
        printf("************* Wrong Option! Try Again *****************\n");
        transfer_point(login_user_index);
    }
}

inline void show_user_point_transaction(int login_user_index) {
    int point_transaction_count = users[login_user_index].point_transaction_count;
    printf("\n*********** Your Point Transactions ***********\n");
    printf("Your Points => %d\n", users[login_user_index].point);

    // Print table header
    printf(
        "---------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-5s %-30s %-5s %-10s %-10s %-10s %-10s %-15s %-25s %-20s\n",
           "No", "Transfer At", "ID", "Type", "Amount", "Before", "After", "Related Name", "Related Email", "Remark");
    printf(
        "---------------------------------------------------------------------------------------------------------------------------------------\n");

    for (int x = 0; x < point_transaction_count; x++) {
        int number = x + 1;
        int related_id = users[login_user_index].point_transaction[x].related_id;

        int related_user_index = get_user_index_by_id(related_id);

        printf("%-5d %-30s %-5d %-10s %-10d %-10d %-10d %-15s %-25s %-20s\n",
               number,
               users[login_user_index].point_transaction[x].transfer_at,
               users[login_user_index].point_transaction[x].id,
               users[login_user_index].point_transaction[x].type,
               users[login_user_index].point_transaction[x].amount,
               users[login_user_index].point_transaction[x].before_amount,
               users[login_user_index].point_transaction[x].after_amount,
               users[related_user_index].name,
               users[related_user_index].email,
               users[login_user_index].point_transaction[x].remark);
        printf(
        "---------------------------------------------------------------------------------------------------------------------------------------\n");

    }
}

void manage_user(int login_user_index) {
    printf("******* Manage Users ********\n");
    int option = 0;
    printf("Enter 1 To See Users\nEnter 2 Ban Users\nEnter 3 To Active User\nEnter 4 To Go Back\n");
    printf("Enter Here => ");
    scanf("%d", &option);

    if (option == 1) {
        show_users();
        manage_user(login_user_index);
    }else if (option == 2) {
        bann_user(login_user_index);
        manage_user(login_user_index);
    }else if (option == 3) {
        active_user(login_user_index);
        manage_user(login_user_index);
    }else if (option == 4) {
        admin_dashboard(login_user_index);
    }else {
        printf("********* Wrong Option *********\n");
        manage_user(login_user_index);
    }

}

inline void show_users() {
    printf("****** User Lists ********\n");
    printf(
       "--------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-5s %-5s %-20s %-20s %-10s %-10s %-10s %-25s %-10s %-20s\n",
           "No", "ID", "Name", "Email", "Phone", "Postcode", "Point", "Transaction Count","Status", "Address");
    printf(
       "--------------------------------------------------------------------------------------------------------------------------------------\n");
    for (int x = 0; x < g_user_count; x++) {
        int number = x + 1;
        printf("%-5d %-5d %-20s %-20s %-10d %-10d %-10d %-25d %-10s %-20s\n",
               number,
               users[x].id,
               users[x].name,
               users[x].email,
               users[x].phone,
               users[x].postcode,
               users[x].point,
               users[x].point_transaction_count,
               users[x].status,
               users[x].address
               );

        printf(
        "--------------------------------------------------------------------------------------------------------------------------------------\n");
    }

};

inline void bann_user(int login_user_index) {
    int option = 0;
    printf("******* Ban User *******\n");
    printf("********** Enter User Email To Ban ************\n");

    int user_index = get_user_index_by_email();
    if (user_index == -1) {
        printf("**** User Not Found ******\n");
        printf("Enter 1 To Retry\nEnter 2 To Go Back\n");
        printf("Enter Here ==> ");
        scanf("%d", &option);
        if (option == 1) {
            bann_user(login_user_index);
        }else if (option == 2) {
            manage_user(login_user_index);
        }else {
            printf("******** Wrong Option *******\n");
            bann_user(login_user_index);
        }
    }

    copy_two_char_array(users[user_index].status, G_STATUS_INACTIVE);

    printf("************ Banned User Successfully ************\n");
}

inline void active_user(int login_user_index) {
    int option = 0;
    printf("******* Active User *******\n");
    printf("********** Enter User Email To Active ************\n");

    int user_index = get_user_index_by_email();
    if (user_index == -1) {
        printf("**** User Not Found ******\n");
        printf("Enter 1 To Retry\nEnter 2 To Go Back\n");
        printf("Enter Here ==> ");
        scanf("%d", &option);
        if (option == 1) {
            active_user(login_user_index);
        }else if (option == 2) {
            manage_user(login_user_index);
        }else {
            printf("******** Wrong Option *******\n");
            active_user(login_user_index);
        }
    }

    copy_two_char_array(users[user_index].status, G_STATUS_ACTIVE);

    printf("************ Active User Successfully ************\n");
}

inline int check_user_active(int user_index) {
    if (check_two_char_array(G_STATUS_ACTIVE, users[user_index].status)) {
        return 1;
    } else {
        return 0;
    }
}


/**
 * Functions End ...............................
 */



#endif //DDSA_N1C_H