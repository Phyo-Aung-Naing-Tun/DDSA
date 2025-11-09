//
// Created by phyo-aung-naing-tun on 10/29/25.
//

#ifndef DDSA_N1C_G_VARIABLES_H
#define DDSA_N1C_G_VARIABLES_H

typedef struct {
    int id;
    int related_id;
    int amount;
    int before_amount;
    int after_amount;
    char type[4]; //in or out
    char remark[50];
    char transfer_at[20];
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
    int point_transaction_count;
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
const char G_IN[4] = "in";
const char G_OUT[4] = "out";

int g_user_count = 0;
int g_login_user_id = 0;
int g_available_user_count = 10;
int g_available_point_transaction_count = 100;
/*
 * global variables
 */

#endif //DDSA_N1C_G_VARIABLES_H