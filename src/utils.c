#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int generic_delete(char *database_path, int id)
{
    FILE *s_file = fopen(database_path, "r+");
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
        char *dest_file_path = malloc((sizeof database_path + sizeof "copy") + 10);
        strcat(dest_file_path, database_path);
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

        rename(dest_file_path, database_path);

        fclose(d_file);
        free(dest_file_path);
    }

    fclose(s_file);
    return 1;
}