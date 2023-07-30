#include "meridb.h"

void free_csv(struct CSV *csv, enum Bool free_strings)
{
    struct StringList *node = csv->string_list;
    struct StringList *next = node->next;

    size_t node_count = csv->rows * csv->columns;

    for (size_t i = 0; i < node_count; ++i)
    {
        printf("%s\n", node->string);
        if (free_strings)
        {
            free(node->string);
        }
        next = node->next;
        free(node);
        node = next;
    }

    free(node);

    free(csv);
}       
