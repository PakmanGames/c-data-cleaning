#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_processing.h"

void free_memory(float **data, int rows) {
    for (int i = 0; i < rows; i++) {
        free(data[i]);
    }
    free(data);
}

float **read_data(int *rows, int *columns) {
    if (scanf("%d %d", rows, columns) != 2) {
        return NULL;
    }

    float **data = malloc(*rows * sizeof(float *));
    if (data == NULL) {
        return NULL;
    }

    for (int i = 0; i < *rows; i++) {
        data[i] = malloc(*columns * sizeof(float));
        if (data[i] == NULL) {
            free_memory(data, i);
            return NULL;
        }
    }

    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *columns; j++) {
            if (scanf("%f", &data[i][j]) != 1) {
                free_memory(data, *rows);
                return NULL;
            }
        }
    }

    printf("Data read success (FOR TESTING)\n");
    return data;
}