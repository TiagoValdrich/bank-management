#include "../include/menu.h"
#include "../include/account.h"
#include <stdio.h>
#include <stdlib.h>

void display_menu() {
    for (int i = 1; i <= NUMBER_OF_MENU_OPTIONS; i++) {
        display_menu_option(i);
    }
}

void display_menu_option(int option) {
    switch (option) {
        case 1:
            printf("1 - Create new account\n\n");
            break;
        case 2:
            printf("2 - Create transaction\n\n");
            break;
        case 3:
            printf("3 - Show transactions\n\n");
            break;
        case 4:
            printf("4 - Show accounts\n\n");
            break;
        case 5:
            printf("5 - Show registered people\n\n");
            break;
        case 6:
            printf("6 - Exit\n\n");
            break;
    }
}

void display_option_interface(int option) {
    switch (option) {
        case 1:
            system("clear");
            display_create_account();
            break;
        case 4:
            system("clear");
            display_account_list();
            break;
        case 6:
            system("clear");
            exit(1);
    }
}