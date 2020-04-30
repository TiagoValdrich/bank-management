#ifndef _ACCOUNT_H
#define _ACCOUNT_H

#include "utils.h"

typedef struct account
{
    long account_number;
    int person_id;
    double balance;
} BANK_ACCOUNT;

static const int QTT_ACCOUNT_FIELDS = 3;
static const KEY_VALUE ACCOUNT_FIELDS[3] = {
    {"id", "int"},
    {"person_id", "int"},
    {"balance", "double"}
};

void display_create_account();
void display_account_list();
int get_next_account_number();
int create_bank_account(BANK_ACCOUNT *bank_account);
BANK_ACCOUNT build_bank_account_struct(char row[1024]);
char *clear_string(char *str);

#endif