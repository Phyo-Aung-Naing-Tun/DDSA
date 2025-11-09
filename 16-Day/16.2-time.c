//
// Created by phyo-aung-naing-tun on 11/1/25.
//

#include "stdio.h"
#include "time.h"
int main() {

    time_t now = time(0);
    char data[30];

    struct tm *tm_info = localtime(&now);

    // printf("%d", tm_info->tm_year + 1900);

    sprintf(
        &data[0],
        "%d-%d-%d %d:%d:%d",
        tm_info->tm_year + 1900,
        tm_info->tm_mon + 1,
        tm_info->tm_mday,
        tm_info->tm_hour,
        tm_info->tm_min,
        tm_info->tm_sec
        );

    printf("%s", data);

    return 0;
}