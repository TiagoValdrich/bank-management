typedef struct person {
    int id;
    char *name;
    char *email;
    int age;
    long document;
} PERSON;

typedef struct account {
    long account_number;
    PERSON p;
    double balance;
} BANK_ACCOUNT;

void display_create_account();
char* clear_string(char *str);
int create_person(PERSON *p);