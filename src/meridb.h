#ifndef MERIDB_H
#define MERIDB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* enums */

enum Bool
{
    BOOL_FALSE = 0,
    BOOL_TRUE = 1
};

/* structs */

struct CSV
{
    struct StringList *string_list;
    size_t rows;
    size_t columns;
};

struct StringList
{
    char *string;
    struct StringList *next;
};

/* convert.c */

extern struct CSV *convert_csv_to_helios(struct CSV *source);

/* parse.c */

extern struct CSV *read_csv(const char *path);

/* util.c */

extern void free_csv(struct CSV *csv, enum Bool free_strings);

/* write.c */

extern void write_csv(const char *path, struct CSV *csv);

#endif
