#include "meridb.h"

char **convert_csv_to_string_array(struct CSV *source)
{
    size_t array_size = source->rows * source->columns;
    char **array = calloc(array_size, sizeof(*array));

    struct StringList *node = source->string_list;

    for (size_t i = 0; i < array_size; ++i)
    {
        array[i] = node->string;
        node = node->next;
    };

    return array;
}

size_t get_input(size_t valid_min, size_t valid_max)
{
    enum Bool valid_input = BOOL_FALSE;

    size_t input = 0;
    while (!valid_input)
    {
        printf("> ");

        fscanf(stdin, "%ld", &input);

        if (valid_min <= input && input <= valid_max)
        {
            valid_input = BOOL_TRUE;
        }
        else
        {
            printf("Invalid input. Try again.\n");
        }
    }

    return input;
}

char *get_string_from_array(char **array, size_t columns, size_t row, size_t column)
{
    return array[columns * (row - 1) + column - 1];
}

struct StringList *push_string_list_node(struct StringList *node, char *string)
{
    node->string = malloc(strlen(string) + 1);
    strcpy(node->string, string);
    node->next = malloc(sizeof(*node));
    node = node->next;

    return node;
}

struct CSV *convert_csv_to_helios(struct CSV *source)
{
    printf("Beginning conversion to Helios-compatible format.\n");

    char **array = convert_csv_to_string_array(source);

    size_t array_size = source->rows * source->columns;

    /*
    for (size_t i = 0; i < array_size; ++i)
    {
        printf("%s\n", array[i]);
    }
    */

    printf("\n");
    printf("Sample row of CSV:\n");

    for (size_t i = 0; i < source->columns; ++i)
    {
        printf("Column %ld: %s\n", i + 1, array[i]);
    }

    printf("\n");
    printf("Enter the number of the column that contains email addresses.\n");
    size_t email_column_id = get_input(1, source->columns);

    printf("Enter the number of the column that contains user logins. (ex. SmithAlex)\n");
    size_t login_column_id = get_input(1, source->columns);

    printf("Enter the number of the column that contains users' names. (ex. Smith, Alex)\n");
    size_t name_column_id = get_input(1, source->columns);

    printf("%ld %ld %ld\n", email_column_id, login_column_id, name_column_id);

    struct CSV *helios_csv = malloc(sizeof(*helios_csv));

    helios_csv->rows = source->rows;
    helios_csv->columns = 4;

    struct StringList *node = malloc(sizeof(*node));
    helios_csv->string_list = node;

    for (size_t i = 0; i < helios_csv->rows; ++i)
    {
        node = push_string_list_node(node, "password");

        node = push_string_list_node(node, get_string_from_array(array, source->columns, i + 1,
            login_column_id));

        node = push_string_list_node(node, get_string_from_array(array, source->columns, i + 1,
            email_column_id));

        node = push_string_list_node(node, get_string_from_array(array, source->columns, i + 1,
            name_column_id));
    }

    for (size_t i = 0; i < array_size; ++i)
    {
        free(array[i]);
    }

    free(array);

    return helios_csv;
}
