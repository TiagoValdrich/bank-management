#include <stdio.h>
#include "../include/person.h"

const char *PERSON_DATABASE_PATH = "database/person.txt";

int create_person(PERSON *p)
{
    FILE *f = fopen(PERSON_DATABASE_PATH, "r+");

    if (f == NULL)
    {
        printf("Error to save person on database");
        return 0;
    }

    p->id = get_next_person_id();

    fprintf(f, "%d", p->id);
    fseek(f, 0, SEEK_END);
    fprintf(f, "\n%d,%s,%s,%d,%ld", p->id, p->name, p->email, p->age, p->document);
    fclose(f);

    return 1;
}

int get_next_person_id()
{
    FILE *f = fopen(PERSON_DATABASE_PATH, "r");
    int next_person_id;

    if (f == NULL)
    {
        printf("Error getting next person id");
        return 0;
    }

    fscanf(f, "%d", &next_person_id);
    fclose(f);

    return (++next_person_id);
}