#include "meridb.h"

#define INIT_BUFFER_CAPACITY    10

char *read_string(FILE *fileptr)
{
    enum Bool end_of_string = BOOL_FALSE;
    enum Bool inside_quotes = BOOL_FALSE;
    size_t char_count = 0;
    long seek_offset = 0;

    while (!end_of_string)
    {
        char c = fgetc(fileptr);
        /* printf("Reading string: %ld\n", ftell(fileptr)); */

        switch (c)
        {
            case ',':

                if (inside_quotes)
                {
                    ++char_count;
                }
                else
                {
                    end_of_string = BOOL_TRUE;
                }

                break;

            case '\n':

                if (char_count > 0)
                {
                    end_of_string = BOOL_TRUE;
                }
                else
                {
                    return NULL;
                }

                break;

            case EOF:

                return NULL;

                break;

            case '\"':

                inside_quotes = BOOL_TRUE;

                break;

            default:

                ++char_count;
        }

        --seek_offset;
    }

    if (inside_quotes)
    {
        ++seek_offset;
    }

    fseek(fileptr, seek_offset, SEEK_CUR);

    size_t string_size = char_count + 1;
    char *string = malloc(string_size * sizeof(char));

    fread(string, sizeof(char), char_count, fileptr);
    string[char_count] = '\0';

    return string;
}

struct CSV *read_csv(const char *path)
{
    FILE *fileptr = fopen(path, "r");
    if (fileptr == NULL)
    {
        fprintf(stderr, "could not open file\n");
    }

    enum Bool end_of_line = BOOL_FALSE;
    enum Bool inside_quotes = BOOL_FALSE;
    size_t column_count = 1;

    printf("Analyzing file...\n");

    while (!end_of_line)
    {
        char c = fgetc(fileptr);
        /* printf("Reading 1st line: %ld\n", ftell(fileptr)); */

        switch (c)
        {
            case ',':

                if (!inside_quotes)
                {
                    ++column_count;
                }

                break;

            case '\"':

                inside_quotes = !inside_quotes;

                break;

            case '\n':
            case EOF:

                end_of_line = BOOL_TRUE;

                break;

            default:

                break;
        }
    }

    fseek(fileptr, 0, SEEK_SET);

    printf("Column count: %ld\n", column_count);

    enum Bool end_of_file = BOOL_FALSE;
    size_t string_count = 0;

    struct StringList *head = malloc(sizeof(*head));
    struct StringList *node = head;

    printf("Reading file...\n");

    while (!end_of_file)
    {
        char c = fgetc(fileptr);
        /* printf("Reading file: %ld\n", ftell(fileptr)); */

        switch (c)
        {
            case ',':
            case ' ':
            case '\n':

                break;

            case EOF:

                end_of_file = BOOL_TRUE;

                break;

            default:
            {
                ungetc(c, fileptr);
                char *string = NULL;
                while (string == NULL && !end_of_file)
                {
                    string = read_string(fileptr);
                    if (fgetc(fileptr) == EOF)
                    {
                        end_of_file = BOOL_TRUE;
                    }
                }
                node->string = string;
                node->next = malloc(sizeof(*node));
                node = node->next;
            }
                ++string_count;

                break;
        }
    }

    printf("Finished reading.\n");

    fclose(fileptr);
    printf("File closed.\n");

    struct CSV *csv = malloc(sizeof(*csv));
    csv->columns = column_count;
    csv->rows = string_count / column_count;
    csv->string_list = head;

    /*
    node = head;

    printf("Contents:\n");

    for (size_t i = 0; i < string_count; ++i)
    {
        printf("%s\n", node->string);
        node = node->next;
    }
    */

    return csv;
}
