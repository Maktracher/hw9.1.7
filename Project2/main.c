#include <stdio.h>
#include "matrix.h"

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int main() {
    int rows, cols;
    printf("Enter the number of rows for the matrix: ");
    scanf("%d", &rows);
    clear_input_buffer();
    printf("Enter the number of columns for the matrix: ");
    scanf("%d", &cols);
    clear_input_buffer();

    MAT mat;
    create_matrix(&mat, rows, cols);
    populate_matrix_auto(&mat);

    printf("Matrix A:\n");
    print_matrix(&mat);

    char result = mat_test_positive_definiteness(&mat);
    if (result == MAT_POSDEF)
        printf("The matrix is positive definite\n");
    else if (result == MAT_POSSEMDEF)
        printf("The matrix is positive semidefinite\n");
    else
        printf("The matrix is not positive definite\n");

    free_matrix(&mat);

    printf("Stlačte Enter pre pokračovanie...");
    getchar();  

    return 0;
}
