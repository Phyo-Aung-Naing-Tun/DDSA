//
// Created by phyo-aung-naing-tun on 10/4/25.
// Intelligent Delivery System (Update Add Point And Point Transaction)
//


/**
 * after finish register, g_user_count was increased and user id will be the previous value of g_user_count
 * after login success, g_login_user_id was set with user_id,
 */


#include <stdio.h>
#include <stdlib.h>

void menu();

void registration();

void login();

int validate_email(char email[50]);

int validate_phone(int phone);

int validate_password(char password[50]);


/**
 * Start Helper Functions
 */

void copy_two_char_array(char destination[50], char data[50]);

int check_two_char_array(char target[50], char data[50]);

int check_email_duplication(char email[50]);

int check_phone_duplication(int phone);

int get_char_array_count(char data[50]);

int get_user_by_id();

int get_user_by_email();

/**
 * End Helper Functions
 */

/**
 * Start After Login
 */

void show_user_dashboard();

void see_user_infos();

void update_user_infos();

int confirm_actual_user();

void logout();

void transfer_point();

/**
 * End After Login
 */

struct Db {
    int id;
    char name[50];
    char email[50];
    char password[50];
    int postcode;
    int phone;
    char address[50];
    int point;
};

struct PointTransactionDb {
    int id;
    int user_id;
    int related_id;
    int amount;
    char type[2]; //in or out
    char remark[50];
};

struct Db users[20];
struct PointTransactionDb point_transactions[1000];

/**
 * Start Global Variables
 */

int g_menu_option = 0;
int g_user_count = 0;
int g_login_user_id = -1;
int g_login_tried_count = 0;
int g_max_allowed_login_tried_count = 3;
int g_point_transaction_count = 0;

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
        } else if (g_menu_option == 3) {
            printf("\n--------------------Bye Bye---------------\n");
            exit(0);
        } else {
            printf("Wrong Choice!\n");
            menu();
        }
    }
}

void registration() {
    printf("\n--------------------Registration Form---------------\n");

    int is_valid_email = 0;
    int is_valid_phone = 0;
    int is_valid_password = 0;

    char r_name[50];
    char r_email[50];
    char r_password[50];
    int r_phone;
    int r_postcode;
    char r_address[50];

    printf("Enter Your Name => ");
    scanf(" %[^\n]", &r_name[0]);

    while (is_valid_email == 0) {
        printf("Enter Your Email => ");
        scanf(" %[^\n]", &r_email[0]);
        is_valid_email = validate_email(r_email);
    }

    while (is_valid_phone == 0) {
        printf("Enter Your Phone => ");
        scanf("%d", &r_phone);
        is_valid_phone = validate_phone(r_phone);
    }

    printf("Enter Your Postcode => ");
    scanf("%d", &r_postcode);

    printf("Enter Your Address => ");
    scanf(" %[^\n]", &r_address[0]);

    while (is_valid_password == 0) {
        printf(
            "Enter Your Password.\nPassword must include at least one small letter,\n one capital letter , one number and\n one special character => ");
        scanf(" %[^\n]", &r_password[0]);

        is_valid_password = validate_password(r_password);
    }

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

    users[g_user_count].postcode = r_postcode;
    printf("Checking User Postcode %d\n", users[g_user_count].postcode);

    copy_two_char_array(users[g_user_count].address, r_address);
    printf("Checking User Address %s\n", users[g_user_count].address);

    users[g_user_count].point = 10000;
    printf("Checking User Point %d\n", users[g_user_count].point);

    g_user_count++;
    printf("\n**** Successfully Registered ****\n");
}

int validate_email(char email[50]) {
    int is_duplicate = check_email_duplication(email);
    int is_valid = 0;

    int is_valid_first_part = 0;
    int is_valid_second_part = 0;
    int second_part_start_at = 0;
    char second_part[50];

    char gmail_symbol[10] = {'@','g','m','a','i','l','.','c','o','m'};
    char apple_mail_symbol[10] = {'@','a','p','p','l','e','.','c','o','m'};
    char yahoo_mail_symbol[10] = {'@','y','a','h','o','o','.','c','o','m'};

    int given_email_count = get_char_array_count(email);

    if (is_duplicate == 1) {
        printf("\n************Your Email Is Already Taken! Please Use Another.**********\n");
        return is_valid;
    }

    for (int x = 0; x < given_email_count; x++) {
        if ( email[x] == '@') {
            second_part_start_at = x;
            break;
        }
        if ((email[x] >= 32 && email[x] <= 47) ||  (email[x] >= 58 && email[x] <= 96) || (email[x] >= 123 && email[x] <= 127)) {
            is_valid_first_part = 0;
            break;
        }

        is_valid_first_part = 1;
    }

    if ( is_valid_first_part == 0 ) {
        printf("\n************Your Email ( %s ) Is Invalid! Please Use Another.**********\n",email);
        return is_valid;
    }

    for (int xx = 0; xx < given_email_count; xx++ ) {
        if (email[xx] == '\0') {
            break;
        }

        second_part[xx] = email[second_part_start_at];
        second_part_start_at++;
    }

    int is_valid_gmail_symbol = check_two_char_array(second_part,gmail_symbol);
    int is_valid_yahoo_mail_symbol = check_two_char_array(second_part,yahoo_mail_symbol);
    int is_valid_apple_mail_symbol = check_two_char_array(second_part,apple_mail_symbol);

    if (is_valid_gmail_symbol || is_valid_yahoo_mail_symbol || is_valid_apple_mail_symbol) {
        is_valid_second_part = 1;
    }

    if (is_valid_first_part && is_valid_second_part) {
        is_valid = 1;
    }else {
        printf("\n************Your Email ( %s ) Is Invalid! Please Use Another.**********\n",email);
    }

    return is_valid;
}

int validate_phone(int phone) {
    int is_valid = 0;
    int is_duplicate = check_phone_duplication(phone);

    if (is_duplicate == 1) {
        printf("\n************Your Phone Is Already Taken! Please Use Another.**********\n");
        is_valid = 0;
    } else {
        is_valid = 1;
    }

    return is_valid;
};

/**
 * must include at least
 * one capital letter,
 * one small letter,
 * one number and
 * one special character.
 */
int validate_password(char password[50]) {
    int is_valid = 0;
    int is_include_capital_letter = 0;
    int is_include_small_letter = 0;
    int is_include_number = 0;
    int is_include_special_character = 0;

    for (int x = 0; x < 50; x++) {
        if (password[x] == '\0') {
            break;
        }
        if (password[x] >= 48 && password[x] <= 57) {
            is_include_number = 1;
        } else if (password[x] >= 97 && password[x] <= 122) {
            is_include_small_letter = 1;
        } else if (password[x] >= 65 && password[x] <= 90) {
            is_include_capital_letter = 1;
        } else if ((password[x] >= 32 && password[x] <= 47) || (password[x] >= 58 && password[x] <= 64) || (
                       password[x] >= 91 && password[x] <= 95) || (password[x] >= 123 && password[x] <= 126)) {
            is_include_special_character = 1;
        }
    }

    if (is_include_capital_letter == 1 && is_include_small_letter == 1 && is_include_number == 1 &&
        is_include_special_character == 1) {
        is_valid = 1;
    } else {
        printf("\n*********Your Email Is Invalid!************.\n");
    }

    return is_valid;
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
    printf("Enter 1 To See Your Information\nEnter 2 To Logout\n");
    printf("Enter 3 To Update Your Information\nEnter 4 To Transfer Point\n");
    printf("Enter 5 To Exit Program\n");
    printf("Enter Here => ");

    scanf("%d", &user_option);

    if (user_option == 1) {
        see_user_infos();
    } else if (user_option == 2) {
        logout();
    } else if (user_option == 3) {
        update_user_infos();
    } else if (user_option == 4) {
        transfer_point();
    }  else if (user_option == 5) {
        exit(0);
    } else {
        printf("Wrong Choice !\n");
        show_user_dashboard();
    }
}


void see_user_infos() {
    int go_back = 0;
    printf("****************Here Your Information***************\n");
    printf("Your Name is  %s. \n", users[g_login_user_id].name);
    printf("Your Email is  %s. \n", users[g_login_user_id].email);
    printf("Your Phone is %d. \n ", users[g_login_user_id].phone);
    printf("Your Postcode is %d. \n ", users[g_login_user_id].postcode);
    printf("Your address is %s. \n ", users[g_login_user_id].address);
    printf("Your Point is %d. \n ", users[g_login_user_id].point);

    printf("Enter 1 to go back ===> ");
    scanf("%d", &go_back);
    if (go_back == 1) {
        show_user_dashboard();
    } else {
        printf("Wrong Choice Enter 1 to go back ===> ");
        scanf("%d", &go_back);
    }
}

void logout() {
    g_login_user_id = -1;
    g_login_tried_count = 0;
    menu();
}

void update_user_infos() {
    if (confirm_actual_user() == 1) {
        int option = 0;
        char new_char_data[50];
        int n_phone = 0;
        int n_postcode = 0;

        printf("Enter 1 To Change User Name\nEnter 2 To Change User Email\n");
        printf("Enter 3 To Change User Phone\nEnter 4 To Change User Password\n");
        printf("Enter 5 To Change User Postcode\nEnter 6 To Change User Address\n");
        printf("Enter 7 To Go Dashboard\n");
        printf("Enter Here => ");
        scanf("%d", &option);

        if (option == 1) {
            printf("Enter Your New User Name => ");
            scanf(" %[^\n]", &new_char_data[0]);
            copy_two_char_array(users[g_login_user_id].name, new_char_data);
        } else if (option == 2) {
            int is_valid_email = 0;

            while (is_valid_email == 0) {
                printf("Enter Your New Email => ");
                scanf(" %[^\n]", &new_char_data[0]);
                is_valid_email = validate_email(new_char_data);
            }

            copy_two_char_array(users[g_login_user_id].email, new_char_data);
        } else if (option == 3) {
            int is_valid_phone = 0;

            while (is_valid_phone == 0) {
                printf("Enter Your New Phone => ");
                scanf("%d", &n_phone);

                is_valid_phone = validate_phone(n_phone);
            }

            users[g_login_user_id].phone = n_phone;

        } else if (option == 4) {
            int is_valid_password = 0;

            if (is_valid_password == 0) {
                printf("Enter Your New Password => ");
                scanf(" %[^\n]", &new_char_data[0]);

                is_valid_password = validate_password(new_char_data);
            }

            copy_two_char_array(users[g_login_user_id].password, new_char_data);

        } else if (option == 5) {

            printf("Enter Your New Postcode => ");

            scanf("%d", &n_postcode);

            users[g_login_user_id].postcode = n_postcode;


        } else if ( option == 6) {

            printf("Enter Your New Address => ");

            scanf(" %[^\n]", &new_char_data[0]);

            copy_two_char_array(users[g_login_user_id].address, new_char_data);

        } else if (option == 7) {
            show_user_dashboard();
        } else {
            printf("Wrong Choice!\n");
            update_user_infos();
        }

        see_user_infos();
    } else {
        printf("** Sorry Your Information Is Wrong!**\n");
        show_user_dashboard();
    }
}

int confirm_actual_user() {
    char c_password[50];
    int result = 0;

    printf("Enter Your Password To Continue =>");
    scanf(" %[^\n]", &c_password[0]);
    result = check_two_char_array(users[g_login_user_id].password, c_password);
    return result;
}

void transfer_point() {

    int target_user_index = -1;
    int option = -1;
    int transfer_retry_option = -1;
    int available_point =  users[g_login_user_id].point;
    int to_transfer_point = 0;
    char remark[50];
    char type_in[2] = {'i','n'};
    char type_out[3] = {'o','u','t'};

    printf("\n***** Transfer Your Point ****\n");
    printf("You have %d point.\n", available_point);
    printf("Enter Receiver Email\n");

        target_user_index = get_user_by_email();

        if (target_user_index == -1 || g_login_user_id == target_user_index) {
            if (g_login_user_id == target_user_index) {
                printf("\nYou Can't Transfer Yourself\n");
            }
            printf("\n Press 1 To Retry and Others To Go Back => ");
            scanf("%d",&option);
            if (option == 1) {
                transfer_point();
            } else {
                show_user_dashboard();
            }
        }

        printf("********Here Receiver Information*********\n");
        printf("Receiver Name is %s\n", users[target_user_index].name);
        printf("Receiver Email is %s\n", users[target_user_index].email);

        printf("Enter amount to transfer => ");
        scanf("%d",&to_transfer_point);

         while(available_point < to_transfer_point) {
            printf("You Dont Have Enough Money\n");
            printf("Enter 1 to retry and Others To Go Back => ");
             scanf("%d",&transfer_retry_option);
             if (transfer_retry_option == 1) {
                 printf("Enter amount to transfer => ");
                 scanf("%d",&to_transfer_point);
             }else {
                 show_user_dashboard();
             }
        }
        printf("Enter Remark => ");
        scanf(" %[^\n]",&remark[0]);

        users[g_login_user_id].point = available_point - to_transfer_point;
        users[target_user_index].point = users[target_user_index].point + to_transfer_point;

        //record for sender
        point_transactions[g_point_transaction_count].id = g_point_transaction_count;
        point_transactions[g_point_transaction_count].user_id = users[g_login_user_id].id;
        point_transactions[g_point_transaction_count].related_id = users[target_user_index].id;
        point_transactions[g_point_transaction_count].amount = to_transfer_point;
        copy_two_char_array(point_transactions[g_point_transaction_count].type,type_out);
        copy_two_char_array(point_transactions[g_point_transaction_count].remark,remark);

        g_point_transaction_count++;

        //record for receiver
        point_transactions[g_point_transaction_count].id = g_point_transaction_count;
        point_transactions[g_point_transaction_count].user_id = users[target_user_index].id;
        point_transactions[g_point_transaction_count].related_id = users[g_login_user_id].id;
        point_transactions[g_point_transaction_count].amount = to_transfer_point;
        copy_two_char_array(point_transactions[g_point_transaction_count].type,type_in);
        copy_two_char_array(point_transactions[g_point_transaction_count].remark,remark);

        g_point_transaction_count++;

        printf("\n********Transfered Point Successfully********\n");

        show_user_dashboard();
}

/**
 * End After Authenticated
 */

/**
 * Start Helper Functions
 */
void copy_two_char_array(char destination[50], char data[50]) {
    for (int x = 0; x < 50; x++) {
        destination[x] = '\0';
    }

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
        if (target[x] == '\0') {
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

int check_email_duplication(char email[50]) {
    int result = 0;
    for (int x = 0; x < g_user_count; x++) {
        result = check_two_char_array(users[x].email, email);
        if (result == 1) {
            break;
        }
    }
    return result;
}

int check_phone_duplication(int phone) {
    int result = 0;
    for (int x = 0; x < g_user_count; x++) {
        if (phone == users[x].phone) {
            result = 1;
            break;
        }
    }
    return result;
}

int get_char_array_count(char data[50]) {
    int count = 0;

    for (int x = 0; x < 50; x++) {
        if ( data[x] == '\0') {
            break;
        }else {
            count++;
        }
    }

    return count;
}

/**
 * if find user, will show user info and return index of user
 * if not will return -1;
 * @return int
 */
int get_user_by_id() {
    int user_index = -1;
    int s_user_id = -1;

    printf("Enter Id => ");
    scanf("%d", &s_user_id);

    for (int x = 0; x < 20; x++) {
        if (users[x].id == s_user_id) {
            user_index = x;
            break;
        }
    }

    if (user_index == -1) {
        printf("\n*** Sorry User Not Found ****\n");
    }

    return user_index;
}

/**
 * if find user, will show user info and return index of user
 * if not will return -1;
 * @return int
 */
int get_user_by_email() {
    int user_index = -1;
    char s_user_email[50];

    printf("Enter Email => ");
    scanf(" %[^\n]", &s_user_email[0]);

    for (int x = 0; x < 20; x++) {

        int is_exist = check_two_char_array(users[x].email, s_user_email);

        if (is_exist == 1) {
            user_index = x;
            break;
        }
    }

    if (user_index == -1) {
        printf("\n*** Sorry User Not Found ****\n");
    }
    return user_index;
}

/**
 * End Helper Functions
 */
