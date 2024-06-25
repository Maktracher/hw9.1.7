#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to create a matrix and allocate memory
void create_matrix(MAT* mat, int rows, int cols) {
    mat->rows = rows;
    mat->cols = cols;
    mat->data = (MATRIX_TYPE**)malloc(rows * sizeof(MATRIX_TYPE*));
    if (mat->data == NULL) {
        fprintf(stderr, "Chyba alokácie pamäte\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < rows; i++) {
        mat->data[i] = (MATRIX_TYPE*)malloc(cols * sizeof(MATRIX_TYPE));
        if (mat->data[i] == NULL) {
            fprintf(stderr, "Chyba alokácie pamäte\n");
            exit(EXIT_FAILURE);
        }
    }
}
// Function to free the allocated memory of a matrix
void free_matrix(MAT* mat) {
    for (int i = 0; i < mat->rows; i++) {
        free(mat->data[i]);
    }
    free(mat->data);
    mat->data = NULL;
}

// Function to print a matrix
void print_matrix(const MAT* mat) {
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            printf("%8.3f ", MAT_ELEM(mat, i, j));
        }
        printf("\n");
    }
}

// Function to fill a matrix automatically with random values
void populate_matrix_auto(MAT* mat) {
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            MAT_ELEM(mat, i, j) = rand() % 20 - 10; // Náhodné hodnoty medzi -10 a 10
        }
    }
}

// Testovanie pozitívnej definitnosti matice
char mat_test_positive_definiteness(const MAT* mat) {
    if (mat->rows != mat->cols) {
        fprintf(stderr, "Matica musí byť štvorcová pre testovanie pozitívnej definitnosti.\n");
        return MAT_NOTPOSDEF; // Matica musí byť štvorcová
    }

    int n = mat->rows;
    MAT L;
    create_matrix(&L, n, n); // Vytvorenie dolného trojuholníka pre Choleského rozklad

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (i + 1); j++) {
            double sum = 0;

            for (int k = 0; k < j; k++)
                sum += MAT_ELEM(&L, i, k) * MAT_ELEM(&L, j, k);

            if (i == j) // Diagonálne prvky
                MAT_ELEM(&L, i, j) = sqrt(MAT_ELEM(mat, i, i) - sum);
            else // Nediagonálne prvky
                MAT_ELEM(&L, i, j) = (1.0 / MAT_ELEM(&L, j, j) * (MAT_ELEM(mat, i, j) - sum));
        }

        if (MAT_ELEM(&L, i, i) <= 0) {
            free_matrix(&L);
            return (MAT_ELEM(&L, i, i) == 0) ? MAT_POSSEMDEF : MAT_NOTPOSDEF;
        }
    }

    free_matrix(&L);
    return MAT_POSDEF;
}

