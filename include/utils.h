#ifndef _UTILS_H
#define _UTILS_H

typedef struct key_value
{
    char *key;
    char *value;
} KEY_VALUE;

static const KEY_VALUE PERSON_FIELDS[5] = {
    {"id", "int"},
    {"name", "string"},
    {"email", "string"},
    {"age", "int"},
    {"document", "long"}};

#endif