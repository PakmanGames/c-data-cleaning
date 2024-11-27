#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clean.h"
#include "data_processing.h"

void usage() {
    printf("Usage: clean [-d]\n");
}

int main(int argc, char *argv[]) {
    int delete_flag = 0;

    if (argc == 2 && strcmp(argv[1], "-d") == 0) {
        delete_flag = 1;
    } else if (argc != 2 && argc != 1) {
        usage();
        return EXIT_FAILURE;
    }

    int rows, columns;
    float **data = read_data(&rows, &columns);

    return EXIT_SUCCESS;
}