#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "data_processing.h"

// Function to free memory
void free_memory(float **data, int rows) {
    for (int i = 0; i < rows; i++) {
        free(data[i]);
    }
    free(data);
}

// Function to read data
float **read_data(int *rows, int *columns) {
    if (scanf("%d %d", rows, columns) != 2) {
        return NULL;
    }

    // Allocate memory for data
    float **data = malloc(*rows * sizeof(float *));
    if (data == NULL) {
        return NULL;
    }

    // Allocate memory for each row
    for (int i = 0; i < *rows; i++) {
        data[i] = malloc(*columns * sizeof(float));
        if (data[i] == NULL) {
            free_memory(data, i);
            return NULL;
        }
    }

    // Read data
    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *columns; j++) {
            if (scanf("%f", &data[i][j]) != 1) {
                free_memory(data, *rows);
                return NULL;
            }
        }
    }

    return data;
}

// Function to impute missing values
void clean_impute(float **data, int rows, int columns) {
    for (int j = 0; j < columns; j++) {
        float sum = 0;
        int count = 0;

        // Calculate mean of column
        for (int i = 0; i < rows; i++) {
            if (!isnan(data[i][j])) {
                sum += data[i][j];
                count++;
            }
        }

        float mean = (count > 0) ? sum / count : 0.0;

        // Replace NaN values with mean
        for (int i = 0; i < rows; i++) {
            if (isnan(data[i][j])) {
                data[i][j] = mean;
            }
        }
    }
}

// Function to delete rows with NaN values
float **clean_delete(float **data, int rows, int columns, int *new_rows, int *new_columns) {
    // Count number of valid rows
    int valid_count = 0;
    for (int i = 0; i < rows; i++) {
        int valid = 1;
        for (int j = 0; j < columns; j++) {
            if (isnan(data[i][j])) {
                valid = 0;
                break;
            }
        }
        if (valid) {
            valid_count++;
        }
    }

    // Allocate memory for cleaned data
    float **cleaned_data = malloc(valid_count * sizeof(float *));
    if (cleaned_data == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return NULL;
    }

    // Copy valid rows to cleaned data
    int valid_index = 0;
    for (int i = 0; i < rows; i++) {
        int valid = 1;
        for (int j = 0; j < columns; j++) {
            if (isnan(data[i][j])) {
                valid = 0;
                break;
            }
        }

        // Copy valid row to cleaned data
        if (valid) {
            cleaned_data[valid_index] = malloc(columns * sizeof(float));
            if (cleaned_data[valid_index] == NULL) {
                fprintf(stderr, "Error: Memory allocation failed.\n");
                free_memory(cleaned_data, valid_index);
                return NULL;
            }
            for (int j = 0; j < columns; j++) {
                cleaned_data[valid_index][j] = data[i][j];
            }
            valid_index++;
        }
    }

    // Set new rows and columns
    *new_rows = valid_count;
    *new_columns = columns;

    return cleaned_data;
}
