#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/account.h"
#include "../include/person.h"
#include "../include/utils.h"

const char *ACCOUNT_DATABASE_PATH = "database/account.txt";
const int MAX_ITEMS_PER_PAGE = 5;

void display_create_account()
{
    int default_string_size = (sizeof(char) * 255);
    int age;
    char *name = malloc(default_string_size);
    char *email = malloc(default_string_size);
    long document;
    double balance;

    printf("\nInsert account titular name: ");
    fgets(name, (default_string_size), stdin);

    name = clear_string(name);

    printf("\nInsert an email address: ");
    fgets(email, (default_string_size), stdin);

    email = clear_string(email);

    printf("\nInsert account titular age: ");
    scanf(" %d", &age);

    printf("\nInsert account titular CPF: ");
    scanf(" %ld", &document);

    printf("\nInsert initial account balance: ");
    scanf(" %le", &balance);

    PERSON p = {0, name, email, age, document};

    int person_created = create_person(&p);

    if (person_created)
    {
        int next_account_number = get_next_account_number();

        BANK_ACCOUNT bank_account = {next_account_number, p.id, balance};

        int bank_account_created = create_bank_account(&bank_account);

        if (!bank_account_created)
        {
            printf("Error creating bank account for person %s", p.name);
            delete_person(p.id);
        }
    }

    free(name);
    free(email);
}

int get_next_account_number()
{
    int next_account_number;
    FILE *f = fopen(ACCOUNT_DATABASE_PATH, "r");

    if (f == NULL)
    {
        printf("Error to get next account number");
        return 0;
    }

    fscanf(f, "%d", &next_account_number);
    fclose(f);

    return (++next_account_number);
}

BANK_ACCOUNT get_account_by_id(int id)
{
    FILE *f = fopen(ACCOUNT_DATABASE_PATH, "r");
    char text_line[1024];
    BANK_ACCOUNT bank_account = generate_empty_bank_account();

    // Ignore first line
    fgets(text_line, sizeof text_line, f);

    while(fgets(text_line, sizeof text_line, f) != NULL)
    {
        char *saved, *token;
        token = __strtok_r(text_line, ",", &saved);
        int account_id = atol(token);

        if (account_id && account_id == id)
        {
            bank_account.account_number = account_id;
            bank_account.person_id = atoi(__strtok_r(text_line, ",", &saved));
            bank_account.balance = atof(__strtok_r(text_line, ",", &saved));

            break;
        }
    }

    fclose(f);

    return bank_account;
}

BANK_ACCOUNT generate_empty_bank_account()
{
    BANK_ACCOUNT bank_account = {
        0.0, // ID
        0, // Person ID
        0.0, // Balance
    };

    return bank_account;
}

int create_bank_account(BANK_ACCOUNT *bank_account)
{
    FILE *f = fopen(ACCOUNT_DATABASE_PATH, "r+");

    if (f == NULL)
    {
        printf("Error to create new bank account");
        return 0;
    }

    fseek(f, 0, SEEK_END);
    fprintf(f, "%ld,%d,%f\n", bank_account->account_number, bank_account->person_id, bank_account->balance);
    fseek(f, 0, SEEK_SET);
    fprintf(f, "%ld", bank_account->account_number);
    fclose(f);

    return 1;
}

int delete_account(int account_id)
{
    return generic_delete(ACCOUNT_DATABASE_PATH, account_id);
}

void display_account_list()
{
    FILE *f = fopen(ACCOUNT_DATABASE_PATH, "r");
    char row[1024];
    int index = 0;

    printf("************         Bank account list         ************\n\n");
    // Ignore first line cause it's last id
    fgets(row, sizeof row, f);

    while(fgets(row, sizeof row, f) != NULL) {
        int break_loop = 0;
        index++;
        print_formated_bank_account_from_row(row);

        if (index == MAX_ITEMS_PER_PAGE) {
            char opt;

            do {
                printf("\n\n\n\n");
                printf("N - Next page    D - Delete account    S - Select account     E - Exit to menu  ");

                scanf("%c", &opt);

                opt = toupper(opt);

                switch(opt) {
                    case 'N':
                        system("clear");
                        continue;
                    case 'S':
                        // @TODO: Create check account details
                        break_loop = 1;
                        break;
                    case 'D':
                        handle_account_deletion();
                        break_loop = 1;
                        break;
                    case 'E':
                        break_loop = 1;
                        break;
                }
            } while (opt != 'D' && opt != 'N' && opt != 'S' && opt != 'E');

            if (break_loop) {
                break;
            }
        }
    }

    char opt;

    do {
        printf("\n\n\n\n");
        printf("D - Delete account    S - Select account     E - Exit to menu  ");
        scanf("%c", &opt);

        opt = toupper(opt);

        switch(opt) {
            case 'S':
                // @TODO: Create check account details
                break;
            case 'D':
                handle_account_deletion();
                break;
            case 'E':
                break;
        }

    } while(opt != 'D' && opt != 'S' && opt != 'E');

    fclose(f);
}

BANK_ACCOUNT build_bank_account_struct(char row[1024])
{
    BANK_ACCOUNT bank_account = {0, 0, 0.0};
    char *token = malloc(255);
    token = strtok(row, ",");

    /** @TODO: find a way to not hardcode table struct/table fields */
    for (int i = 0; i < 3; i++) {
        if (i == 0) {
            bank_account.account_number = atol(token);
        } else if (i == 1) {
            bank_account.person_id = atoi(token);
        } else if (i == 2) {
            bank_account.balance = atof(token);
        }
        token = strtok(NULL, ",");
    }

    free(token);
    return bank_account;
}

void handle_account_deletion()
{
    system("clear");

    int account_id;

    printf("\n\nInsert the account number that you want to delete: ");
    scanf("%d", &account_id);

    BANK_ACCOUNT bank_account = get_account_by_id(account_id);

    if (bank_account.account_number != 0 && bank_account.account_number == account_id) {
        int success_account = delete_account(account_id);
        int success_person = delete_person(bank_account.person_id);

        if (success_account && success_person) {
            printf("\n Bank account deleted!\n");
        } else {
            printf("\n Error deleting bank account!\n");
        }
    } else {
        printf("\nAccount not found!\n");
    }
}

void print_formated_bank_account_from_row(char row[1024])
{
    char *token, *saved;
    token = __strtok_r(row, ",", &saved);

    printf("\n");

    /** @TODO: find a way to not hardcode table struct/table fields */
    for (int i = 0; i < 3; i++) {
        if (i == 0) {
            printf("Account number: %s\n", token);
        } else if (i == 1) {
            PERSON p = get_person_by_id(atoi(token));
            printf("Account owner: %s\n", p.name);
        } else if (i == 2) {
            printf("Current balance: %s\n", token);
        }

        token = __strtok_r(NULL, ",", &saved);
    }

    printf("**********\n");
}

char *clear_string(char *str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == '\n')
        {
            str[i] = 0;
        }
    }

    return str;
}