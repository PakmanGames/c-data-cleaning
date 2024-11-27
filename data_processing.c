#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_processing.h"

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
            for (int j = 0; j < i; j++) {
                free(data[j]);
            }
            free(data);
            return NULL;
        }
    }

    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *columns; j++) {
            if (scanf("%f", &data[i][j]) != 1) {
                for (int k = 0; k <= i; k++) {
                    free(data[k]);
                }
                free(data);
                return NULL;
            }
        }
    }

    printf("Data read success (FOR TESTING)\n");
    return data;
}