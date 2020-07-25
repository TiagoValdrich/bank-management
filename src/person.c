#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/person.h"
#include "../include/utils.h"

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
    fprintf(f, "%d,%s,%s,%d,%ld\n", p->id, p->name, p->email, p->age, p->document);
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

int delete_person(int id)
{
    return generic_delete(PERSON_DATABASE_PATH, id);
}

int person_exists(int id) 
{
    FILE *f = fopen(PERSON_DATABASE_PATH, "r");
    char text_line[1024];

    // Ignore first line
    fgets(text_line, sizeof text_line, f);

    while(fgets(text_line, sizeof text_line, f) != NULL)
    {
        int person_id = atoi(strtok(text_line, ","));

        if (person_id && (person_id == id))
        {
            return 1;
        }
    }

    fclose(f);

    return 0;
}

PERSON generate_empty_person()
{
    PERSON p = {
        0, // ID
        "none", // Name
        "none", // Email
        0, // Age
        0 // Document
    };

    return p;
}

PERSON get_person_by_id(int id)
{
    FILE *f = fopen(PERSON_DATABASE_PATH, "r");
    char text_line[1024];
    PERSON p = generate_empty_person();

    // Ignore first line
    fgets(text_line, sizeof text_line, f);

    while(fgets(text_line, sizeof text_line, f) != NULL)
    {
        char *saved, *token;
        token = __strtok_r(text_line, ",", &saved);
        int person_id = atoi(token);

        if (person_id && (person_id == id))
        {
            p.id = person_id;
            p.name = __strtok_r(NULL, ",", &saved);
            p.email = __strtok_r(NULL, ",", &saved);
            p.age = atoi(__strtok_r(NULL, ",", &saved));
            p.document = atol(__strtok_r(NULL, ",", &saved));

            break;
        }
    }

    fclose(f);

    return p;
}