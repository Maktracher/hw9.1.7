#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
    int rows;
    int cols;
    double** data;
} MAT;

#define MAT_POSDEF 1
#define MAT_POSSEMDEF 2
#define MAT_NOTPOSDEF 0

void create_matrix(MAT* mat, int rows, int cols);
void free_matrix(MAT* mat);
void print_matrix(MAT* mat);
void populate_matrix_auto(MAT* mat);
char mat_test_positive_definiteness(MAT* mat);

#endif
