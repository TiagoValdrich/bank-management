#include <stdio.h>
#include <stdlib.h>
#include "../include/menu.h"

int main()
{
    do
    {
        printf("               WELCOME TO BANK MANAGEMENT SYSTEM               \n\n\n");
        display_menu();

        int option;
        scanf(" %d", &option);

        // Cleaning buffer
        while ((getchar()) != '\n');

        display_option_interface(option);
    } while (1);
}