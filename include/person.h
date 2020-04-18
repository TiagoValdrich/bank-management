
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

#endif