/*
    Project objectives:

        -> Display menu
        -> Create an account
        -> Update account information
        -> View and manage transactions
        -> See account details
        -> Remove account
        -> See account list
*/

#include <stdio.h>
#include <stdlib.h>
#include "../include/menu.h"

int main() {
    do {
        printf("               WELCOME TO BANK MANAGEMENT SYSTEM               \n\n\n");
        display_menu();

        int option;
        scanf(" %d", &option);

        while ((getchar()) != '\n');

        display_option_interface(option);
    } while (0);
}