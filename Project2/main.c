// Main function
int main() {
    int rows, cols;
    printf("Enter the number of rows for the matrix: ");
    scanf("%d", &rows);
    printf("Enter the number of columns for the matrix: ");
    scanf("%d", &cols);

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

    return 0;
}
