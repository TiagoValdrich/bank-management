#ifndef _PERSON_H
#define _PERSON_H

typedef struct person
{
    int id;
    char *name;
    char *email;
    int age;
    long document;
} PERSON;

int create_person(PERSON *p);
int get_next_person_id();
int delete_person(int id);
int person_exists(int id);
PERSON generate_empty_person();
PERSON get_person_by_id(int id);

#endif