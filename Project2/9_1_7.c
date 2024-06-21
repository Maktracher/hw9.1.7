#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#pragma warning(disable:4996)

#define MAT_POSDEF 1
#define MAT_POSSEMDEF 2
#define MAT_NOTPOSDEF 0

typedef struct {
    int rows;
    int cols;
    double** data;
} MAT;

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

int main() {
    int size;
    printf("Enter the size n of the n x 2 matrix: ");
    scanf("%d", &size);
    printf("Enter the number of columns for the matrix: ");
    scanf("%d", &cols);
   
    MAT mat;
    create_matrix(&mat, rows, cols);
    

    printf("Matrix A:\n");
    print_matrix(&mat);

}