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


int main() {
    int size;
    printf("¬ведите размер n матрицы n x 2: ");
    scanf("%d", &size);

}