#ifndef MATRIX_H
#define MATRIX_H




typedef struct {
    unsigned int rows;
    unsigned int cols;
    float* elem;
} MAT;

// Helper function to access matrix elements
#define ELEM(mat, i, j) (mat->elem[(i) * mat->cols + (j)])

MAT* mat_create_with_type(unsigned int rows, unsigned int cols);
void mat_destroy(MAT* mat);
void mat_unit(MAT* mat);
void mat_random(MAT* mat);
void mat_print(MAT* mat);
char mat_save(MAT* mat, char* filename);
MAT* mat_create_by_file(char* filename);
char mat_test_positive_definiteness(MAT* mat);

#endif // MATRIX_H
