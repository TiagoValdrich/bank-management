#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/account.h"
#include "../include/person.h"

const char *ACCOUNT_DATABASE_PATH = "database/account.txt";

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

int create_bank_account(BANK_ACCOUNT *bank_account)
{
    FILE *f = fopen(ACCOUNT_DATABASE_PATH, "r+");

    if (f == NULL)
    {
        printf("Error to create new bank account");
        return 0;
    }

    fseek(f, 0, SEEK_END);
    fprintf(f, "\n%ld,%d,%f", bank_account->account_number, bank_account->person_id, bank_account->balance);
    fseek(f, 0, SEEK_SET);
    fprintf(f, "%ld", bank_account->account_number);
    fclose(f);

    return 1;
}

void display_account_list()
{
    FILE *f = fopen(ACCOUNT_DATABASE_PATH, "r");
    char row[1024];

    // Ignore first line cause it's last id
    fgets(row, sizeof row, f);

    while(fgets(row, sizeof row, f) != NULL) {
        build_bank_account_struct(row);
    }

    fclose(f);
}

BANK_ACCOUNT build_bank_account_struct(char row[1024])
{
    char *token = malloc(255);
    token = strtok(row, ",");

    for (int i = 0; i < QTT_ACCOUNT_FIELDS; i++) {
        printf("%s", ACCOUNT_FIELDS[i].key);
    }

    while(token != NULL) {
        printf("%s \n", token);
        token = strtok(NULL, ",");
    }

    free(token);
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