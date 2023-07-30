#include "meridb.h"

void write_csv(const char *path, struct CSV *csv)
{
    struct StringList *node = csv->string_list;

    FILE *fileptr = fopen(path, "w");

    for (size_t rows = 0; rows < csv->rows; ++rows)
    {
        for(size_t columns = 0; columns < csv->columns; ++columns)
        {
            enum Bool quoted = BOOL_FALSE;
            for (size_t i = 0; i < strlen(node->string); ++i)
            {
                if (node->string[i] == ',')
                {
                    quoted = BOOL_TRUE;
                }
            }

            if (quoted)
            {
                fputc('\"', fileptr);
            }

            fputs(node->string, fileptr);
            node = node->next;

            if (quoted)
            {
                fputc('\"', fileptr);
            }

            char c = (columns < csv->columns - 1) ? ',' : '\n';
            fputc(c, fileptr);
        }
    }

    fclose(fileptr);    
}
