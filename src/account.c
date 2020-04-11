#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/account.h"

void display_create_account() {
    int default_string_size = (sizeof(char) * 255);
    char *name = malloc(default_string_size);
    char *email = malloc(default_string_size);
    int age;
    long document;

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

    PERSON p = {0, name, email, age, document};

    int person_created = create_person(&p);

    free(name);
    free(email);
}

char* clear_string(char *str) {
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == '\n') {
            str[i] = 0;
        }
    }

    return str;
}

int create_person(PERSON *p) {
    FILE *f;

    f = fopen("database/person.txt", "r+");

    if (f == 0) {
        printf("Error to save person on database");
        return 0;
    }

    int next_id;
    fscanf(f, "%d", &next_id);
    next_id++;
    p->id = next_id;

    fseek(f, 0, SEEK_SET);
    fprintf(f, "%d", next_id);

    fseek(f, 0, SEEK_END);
    fprintf(f, "\n%d,%s,%s,%d,%ld", p->id, p->name, p->email, p->age, p->document);

    fclose(f);

    return 1;
}