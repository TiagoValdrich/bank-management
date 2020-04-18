#ifndef _ACCOUNT_H
#define _ACCOUNT_H

#include "person.h"

typedef struct account
{
    long account_number;
    int person_id;
    double balance;
} BANK_ACCOUNT;

void display_create_account();
int get_next_account_number();
int create_bank_account(BANK_ACCOUNT *bank_account);
char *clear_string(char *str);

#endif