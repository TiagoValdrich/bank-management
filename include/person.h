#ifndef _PERSON_H
#define _PERSON_H

#include "utils.h"

typedef struct person
{
    int id;
    char *name;
    char *email;
    int age;
    long document;
} PERSON;

static const KEY_VALUE PERSON_FIELDS[5] = {
    {"id", "int"},
    {"name", "string"},
    {"email", "string"},
    {"age", "int"},
    {"document", "long"}};

int create_person(PERSON *p);
int get_next_person_id();
int delete_person(int id);

#endif