#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

int delete_person(int id)
{
    FILE *s_file = fopen(PERSON_DATABASE_PATH, "r+");
    char text_line[1024];
    int line_to_delete = 0;
    int current_line = 1;

    // Ignore first line because is current id index
    fgets(text_line, sizeof text_line, s_file);

    while (fgets(text_line, sizeof text_line, s_file) != NULL)
    {
        current_line++;
        int db_id = atoi(strtok(text_line, ","));

        if (db_id && (db_id == id))
        {
            line_to_delete = current_line;
            break;
        }
    }

    if (line_to_delete != 0)
    {
        // Sets source db file pointer to start of file
        rewind(s_file);
        current_line = 1;
        // Build new db file without the line to delete
        char *dest_file_path = malloc((sizeof PERSON_DATABASE_PATH + sizeof "copy") + 1);
        strcat(dest_file_path, PERSON_DATABASE_PATH);
        strcat(dest_file_path, "copy");
        // Create new file
        FILE *d_file = fopen(dest_file_path, "w");

        // Start populate copy file
        fgets(text_line, sizeof text_line, s_file);
        fprintf(d_file, "%s", text_line);

        while (fgets(text_line, sizeof text_line, s_file) != NULL)
        {
            current_line++;

            if (current_line != line_to_delete && strlen(text_line) != 1)
            {
                fprintf(d_file, "%s", text_line);
            }
        }

        rename(dest_file_path, PERSON_DATABASE_PATH);

        fclose(d_file);
        free(dest_file_path);
    }

    fclose(s_file);
    return 1;
}