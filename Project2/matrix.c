#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable:4996)

MAT* mat_create_with_type(unsigned int rows, unsigned int cols) {
    MAT* mat = (MAT*)malloc(sizeof(MAT));
    if (mat == NULL) {
        
        exit(1);
    }

    mat->rows = rows;
    mat->cols = cols;
    mat->elem = (float*)malloc(rows * cols * sizeof(float));
    if (mat->elem == NULL) {
        free(mat);
        exit(1);
    }

    return mat;
}

void mat_destroy(MAT* mat) {
    if (mat != NULL) {
        free(mat->elem);
        free(mat);
    }
}

void mat_unit(MAT* mat) {
    if (mat == NULL || mat->elem == NULL) {
        
        exit(1);
    }

    unsigned int i, j;
    for (i = 0; i < mat->rows; ++i) {
        for (j = 0; j < mat->cols; ++j) {
            ELEM(mat, i, j) = (i == j) ? 1.0 : 0.0;
        }
    }
}

void mat_random(MAT* mat) {
    if (mat == NULL || mat->elem == NULL) {
        
        exit(1);
    }

    unsigned int i, j;
    for (i = 0; i < mat->rows; ++i) {
        for (j = 0; j < mat->cols; ++j) {
            ELEM(mat, i, j) = ((float)rand() / RAND_MAX) * 2.0 - 1.0;
        }
    }
}

void mat_print(MAT* mat) {
    if (mat == NULL || mat->elem == NULL) {
        
        exit(1);
    }

    unsigned int i, j;
    for (i = 0; i < mat->rows; ++i) {
        for (j = 0; j < mat->cols; ++j) {
            printf("%8.3f ", ELEM(mat, i, j));
        }
        printf("\n");
    }
}

char mat_save(MAT* mat, char* filename) {
    if (mat == NULL || mat->elem == NULL) {
        
        exit(1);
    }

    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        
        exit(1);
    }

    // Write header "M1"
    fwrite("M1", sizeof(char), 2, file);

    // Write number of rows and columns
    fwrite(&(mat->rows), sizeof(unsigned int), 1, file);
    fwrite(&(mat->cols), sizeof(unsigned int), 1, file);

    // Write matrix elements
    fwrite(mat->elem, sizeof(float), mat->rows * mat->cols, file);

    fclose(file);
    return 1;
}

MAT* mat_create_by_file(char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        
        exit(1);
    }

    // Read and validate header "M1"
    char header[2];
    fread(header, sizeof(char), 2, file);
    if (header[0] != 'M' || header[1] != '1') {
        
        fclose(file);
        exit(1);
    }

    // Read number of rows and columns
    unsigned int rows, cols;
    fread(&rows, sizeof(unsigned int), 1, file);
    fread(&cols, sizeof(unsigned int), 1, file);

    // Allocate memory for MAT structure and matrix elements
    MAT* mat = mat_create_with_type(rows, cols);
    if (mat == NULL) {
        
        fclose(file);
        exit(1);
    }

    // Read matrix elements
    fread(mat->elem, sizeof(float), rows * cols, file);

    fclose(file);
    return mat;
}

char mat_test_positive_definiteness(MAT* mat) {
    if (mat == NULL || mat->elem == NULL || mat->rows != mat->cols) {
        
        exit(1);
    }

    // Check positive definiteness
    unsigned int n = mat->rows;
    unsigned int i, j;
    float sum;

    // Check if all leading principal minors are positive
    for (i = 1; i <= n; ++i) {
        // Calculate determinant of the submatrix
        sum = 0;
        for (j = 0; j < i; ++j) {
            sum += ELEM(mat, j, j); // Correctly access elements of mat
        }

        if (sum <= 0) {
            return 0; // Not positive definite
        }
    }

    return 1; // Matrix is positive definite
}

