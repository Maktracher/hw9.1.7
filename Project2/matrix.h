#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>

// Typ dát pre ukladanie prvkov matice
typedef double MATRIX_TYPE;

// Štruktúra pre maticu
typedef struct {
    int rows;         // Počet riadkov
    int cols;         // Počet stĺpcov
    MATRIX_TYPE** data; // Dvojrozmerné pole dát
} MAT;

// Makro na prístup k prvku matice
#define MAT_ELEM(mat, i, j) ((mat)->data[(i)][(j)])

// Prototypy funkcií
void create_matrix(MAT* mat, int rows, int cols);
void free_matrix(MAT* mat);
void print_matrix(const MAT* mat);
void populate_matrix_auto(MAT* mat);


#define MAT_POSDEF 1       
#define MAT_POSSEMDEF 0    
#define MAT_NOTPOSDEF -1

char mat_test_positive_definiteness(const MAT* mat);

#endif // MATRIX_H
