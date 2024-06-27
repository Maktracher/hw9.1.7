#include <stdio.h>
#include "matrix.h"

int main() {
    unsigned int rows, cols;
    printf("Enter the number of rows for the matrix: ");
    scanf("%u", &rows);
    printf("Enter the number of columns for the matrix: ");
    scanf("%u", &cols);

    // Create matrix and initialize with random values
    MAT* mat = mat_create_with_type(rows, cols);
    if (mat == NULL) {
        fprintf(stderr, "Error: Failed to create matrix\n");
        return 1;
    }

    mat_random(mat);

    // Print randomly initialized matrix
    printf("Randomly initialized matrix:\n");
    mat_print(mat);

    // Test positive definiteness
    char result = mat_test_positive_definiteness(mat);
    if (result) {
        printf("The matrix is positive definite.\n");
    }
    else {
        printf("The matrix is not positive definite.\n");
    }

    // Save matrix to file
    char filename[] = "matrix.dat";
    printf("Saving matrix to file '%s'...\n", filename);
    if (mat_save(mat, filename)) {
        printf("Matrix saved successfully.\n");
    }
    else {
        fprintf(stderr, "Error: Failed to save matrix to file.\n");
    }

    // Load matrix from file
    printf("Loading matrix from file '%s'...\n", filename);
    MAT* loaded_mat = mat_create_by_file(filename);
    if (loaded_mat == NULL) {
        fprintf(stderr, "Error: Failed to load matrix from file.\n");
    }
    else {
        printf("Loaded matrix:\n");
        mat_print(loaded_mat);

        // Test positive definiteness
        result = mat_test_positive_definiteness(loaded_mat);
        if (result) {
            printf("The loaded matrix is positive definite.\n");
        }
        else {
            printf("The loaded matrix is not positive definite.\n");
        }

        // Clean up
        mat_destroy(loaded_mat);
    }

    mat_destroy(mat);

    printf("Press Enter to exit the program...\n");
    getchar();
    getchar();
    return 0;
}
