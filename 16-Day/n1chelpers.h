//
// Created by phyo-aung-naing-tun on 10/29/25.
//

#ifndef DDSA_N1CHELPERS_H
#define DDSA_N1CHELPERS_H

#include "stdio.h"
#include "n1c_g_variables.h"
#include "time.h"


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

int get_user_index_by_id(int id);

void set_now(char target[20]);

/**
 * Helpers End ...............................
 */


/**
 * Helpers Start .............................
 */

inline int check_phone_duplication(int phone) {
    for (int x = 0; x < g_user_count; x++) {
        if (users[x].phone == phone) {
            return 1;
        }
    }
    return 0;
}

inline int check_email_duplication(char email[50]) {
    for (int x = 0; x < g_user_count; x++) {
        int is_same = check_two_char_array(users[x].email, email);
        if (is_same) {
            return 1;
        }
    }
    return 0;
}


inline void copy_two_char_array(char target[50], char data[50]) {
    int target_size = get_char_array_count(target);
    int data_size = get_char_array_count(data);

    for (int x = 0; x < target_size; x++) {
        target[x] = '\0';
    }
    for (int x = 0; x < data_size; x++) {
        if (data[x] == '\0') {
            break;
        }
        target[x] = data[x];
    }
}

inline int check_two_char_array(char target[50], char data[50]) {
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

inline int get_char_array_count(char data[50]) {
    int size = 0;
    for (int x = 0; x < 50; x++) {
        if (data[x] == '\0') {
            break;
        }
        size++;
    }
    return size;
}

inline int is_number(char data) {
    if (data >= 48 && data <= 57) {
        return 1;
    }
    return 0;
}

inline int is_small_letter(char data) {
    if (data >= 97 && data <= 122) {
        return 1;
    }
    return 0;
}

inline int is_capital_letter(char data) {
    if (data >= 65 && data <= 90) {
        return 1;
    }
    return 0;
}

inline int is_special_character(char data) {
    if ((data >= 32 && data <= 47) || (data >= 58 && data <= 64) || (data >= 91 && data <= 96) || (
            data >= 123 && data <= 126)) {
        return 1;
    }
    return 0;
}

inline int get_auth_user_index() {
    int login_user_index = -1;
    for (int x = 0; x < g_user_count; x++) {
        if (users[x].id == g_login_user_id) {
            login_user_index = x;
            break;
        }
    }
    return login_user_index;
}

inline int get_user_index_by_email() {
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

inline int get_user_index_by_id(int id) {
    int user_index = -1;
    for (int x = 0; x < g_user_count; x++) {
        if (users[x].id == id) {
            user_index = x;
            break;
        }
    }
    return user_index;
}

inline void set_now(char target[20]) {

    time_t data = time(0);

    struct tm *time_info = localtime(&data);

    sprintf(
        &target[0],
        "%d-%d-%d %d:%d:%d",
        time_info->tm_year + 1900,
        time_info->tm_mon + 1,
        time_info->tm_mday,
        time_info->tm_hour,
        time_info->tm_min,
        time_info->tm_sec
        );
}

/**
 * Helpers End ...............................
 */

#endif //DDSA_N1CHELPERS_H