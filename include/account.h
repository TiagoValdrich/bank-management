#ifndef _ACCOUNT_H
#define _ACCOUNT_H

typedef struct account
{
    long account_number;
    int person_id;
    double balance;
} BANK_ACCOUNT;

void display_create_account();
void display_account_list();
BANK_ACCOUNT get_account_by_id(int id);
BANK_ACCOUNT generate_empty_bank_account();
int get_next_account_number();
int create_bank_account(BANK_ACCOUNT *bank_account);
BANK_ACCOUNT build_bank_account_struct(char row[1024]);
void print_formated_bank_account_from_row(char row[1024]);
void show_account_details();
void handle_account_deletion();
char *clear_string(char *str);

#endif