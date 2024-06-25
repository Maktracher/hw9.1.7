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

    printf("Matica A:\n");
    print_matrix(&mat);

    if (rows != cols) {
        printf("Matica nie je štvorcová a nemôže byť testovaná na pozitívnu definitnosť.\n");
    }
    else {
        char result = mat_test_positive_definiteness(&mat);
        if (result == MAT_POSDEF)
            printf("Matica je pozitívne definitná\n");
        else if (result == MAT_POSSEMDEF)
            printf("Matica je pozitívne semidefinitná\n");
        else
            printf("Matica nie je pozitívne definitná\n");
    }

    free_matrix(&mat);

    printf("Stlačte Enter pre pokračovanie...");
    getchar();


    return 0;
}
