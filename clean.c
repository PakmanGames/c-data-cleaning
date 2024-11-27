#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clean.h"
#include "data_processing.h"

void usage() {
    printf("Usage: clean [-d]\n");
}

void output_data(float **data, int rows, int columns) {
    printf("%d %d\n", rows, columns);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%f ", data[i][j]);
        }
        printf("\n");
    }
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

    if (delete_flag) {
        int new_rows, new_columns;
        float **new_data = clean_delete(data, rows, columns, &new_rows, &new_columns);
        free_memory(data, rows);
        data = new_data;
        rows = new_rows;
        columns = new_columns;

        output_data(data, rows, columns);
    } else {
        clean_impute(data, rows, columns);
        output_data(data, rows, columns);
    }

    free_memory(data, rows);
    return EXIT_SUCCESS;
}