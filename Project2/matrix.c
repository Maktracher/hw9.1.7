#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to create a matrix and allocate memory
void create_matrix(MAT* mat, int rows, int cols) {
    mat->rows = rows;
    mat->cols = cols;
    mat->data = (double**)malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; i++) {
        mat->data[i] = (double*)malloc(cols * sizeof(double));
    }
}

// Function to free the allocated memory of a matrix
void free_matrix(MAT* mat) {
    for (int i = 0; i < mat->rows; i++) {
        free(mat->data[i]);
    }
    free(mat->data);
}

// Function to print a matrix
void print_matrix(MAT* mat) {
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            printf("%8.3f ", mat->data[i][j]);
        }
        printf("\n");
    }
}

// Function to fill a matrix automatically with random values
void populate_matrix_auto(MAT* mat) {
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            mat->data[i][j] = rand() % 20 - 10; // Random values between -10 and 10
        }
    }
}

// Function to test positive definiteness of a matrix using Cholesky decomposition
char mat_test_positive_definiteness(MAT* mat) {
    if (mat->rows != mat->cols) {
        return MAT_NOTPOSDEF; // Matrix must be square
    }

    int n = mat->rows;
    double** A = mat->data;
    MAT L;
    create_matrix(&L, n, n); // Create a matrix for the lower triangular decomposition

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (i + 1); j++) {
            double sum = 0;

            for (int k = 0; k < j; k++)
                sum += L.data[i][k] * L.data[j][k];

            if (i == j) // Diagonal elements
                L.data[i][j] = sqrt(A[i][i] - sum);
            else // Non-diagonal elements
                L.data[i][j] = (1.0 / L.data[j][j] * (A[i][j] - sum));
        }

        if (L.data[i][i] <= 0) {
            free_matrix(&L);
            return (L.data[i][i] == 0) ? MAT_POSSEMDEF : MAT_NOTPOSDEF;
        }
    }

    free_matrix(&L);
    return MAT_POSDEF;
}

