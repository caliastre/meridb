#include "meridb.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s [infile] [outfile]\n", argv[0]);
        return 1;
    }

    struct CSV *csv = read_csv(argv[1]);

    struct CSV *helios = convert_csv_to_helios(csv);
    free_csv(csv, BOOL_FALSE);

    write_csv(argv[2], helios);

    free_csv(helios, BOOL_TRUE);
    return 0;
}
