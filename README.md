
```markdown
# Projekt na prácu s maticami

Tento projekt je určený na prácu s maticami vrátane automatického vypĺňania, tlače a testovania matice na pozitívnu definitnosť.

## Štruktúra projektu

Projekt pozostáva z troch hlavných súborov:

- `main.c`: Hlavný súbor, ktorý obsahuje funkciu `main` pre spustenie programu a interakciu s používateľom.
- `matrix.c`: Súbor, ktorý obsahuje definície funkcií na prácu s maticami.
- `matrix.h`: Hlavičkový súbor, ktorý obsahuje deklarácie funkcií a typov, ktoré sa používajú v `matrix.c`.

## Obsah súborov

### `main.c`

```c
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
```

### `matrix.c`

```c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

void create_matrix(MAT* mat, int rows, int cols) {
    mat->rows = rows;
    mat->cols = cols;
    mat->data = (double**)malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; i++) {
        mat->data[i] = (double*)malloc(cols * sizeof(double));
    }
}

void free_matrix(MAT* mat) {
    for (int i = 0; i < mat->rows; i++) {
        free(mat->data[i]);
    }
    free(mat->data);
}

void print_matrix(MAT* mat) {
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            printf("%8.3f ", mat->data[i][j]);
        }
        printf("\n");
    }
}

void populate_matrix_auto(MAT* mat) {
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            mat->data[i][j] = rand() % 20 - 10;
        }
    }
}

char mat_test_positive_definiteness(MAT* mat) {
    if (mat->rows != mat->cols) {
        return MAT_NOTPOSDEF;
    }

    int n = mat->rows;
    double** A = mat->data;
    MAT L;
    create_matrix(&L, n, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (i + 1); j++) {
            double sum = 0;

            for (int k = 0; k < j; k++)
                sum += L.data[i][k] * L.data[j][k];

            if (i == j)
                L.data[i][j] = sqrt(A[i][i] - sum);
            else
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
```

### `matrix.h`

```c
#ifndef MATRIX_H
#define MATRIX_H

#define MAT_POSDEF 1
#define MAT_POSSEMDEF 2
#define MAT_NOTPOSDEF 0

typedef struct {
    int rows;
    int cols;
    double** data;
} MAT;

void create_matrix(MAT* mat, int rows, int cols);
void free_matrix(MAT* mat);
void print_matrix(MAT* mat);
void populate_matrix_auto(MAT* mat);
char mat_test_positive_definiteness(MAT* mat);

#endif
```

## Inštrukcie na kompiláciu

Na kompiláciu projektu použite `Makefile`. Použite nasledujúce príkazy na kompiláciu a spustenie programu:

### Kompilácia projektu

```sh
mingw32-make
```

### Vyčistenie projektu

```sh
mingw32-make clean
```

### Spustenie programu

```sh
./main
```

## Štruktúra `Makefile`

```makefile
# Makefile

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
LDFLAGS = -Wl,-subsystem,console

# Všetky objektové súbory
OBJ = main.o matrix.o

# Cieľový súbor
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

main.o: main.c matrix.h
	$(CC) $(CFLAGS) -c main.c

matrix.o: matrix.c matrix.h
	$(CC) $(CFLAGS) -c matrix.c

clean:
	rm -f $(OBJ) $(TARGET)
```

