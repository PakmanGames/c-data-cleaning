float **read_data(int *rows, int *columns);
float **clean_delete(float **data, int rows, int columns, int *new_rows, int *new_columns);
void clean_impute(float **data, int rows, int columns);