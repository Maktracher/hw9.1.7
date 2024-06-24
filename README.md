

### Overview

This project provides a C program to test the positive definiteness of a matrix using Cholesky decomposition. It allows for matrix creation, automatic population with random values, and determination of whether a matrix is positive definite, positive semidefinite, or not positive definite.

### Features

- **Matrix Creation**: Dynamically allocate memory for matrices.
- **Automatic Matrix Population**: Fill matrices with random values.
- **Matrix Printing**: Print matrices to the console.
- **Positive Definiteness Test**: Check if a matrix is positive definite using Cholesky decomposition.

### Files

- `matrix_posdef_test.c`: Contains all the source code, including functions for matrix handling and positive definiteness testing.

### Dependencies

- C Standard Library (`<stdio.h>`, `<stdlib.h>`, `<math.h>`)

### Usage

1. **Clone the Repository**:
   ```sh
   git clone https://github.com/username/positive-definiteness.git
   cd positive-definiteness
   ```

2. **Compile the Program**:
   ```sh
   gcc -o matrix_posdef_test matrix_posdef_test.c -lm
   ```

3. **Run the Program**:
   ```sh
   ./matrix_posdef_test
   ```

4. **Follow Prompts**:
   - Enter the number of rows and columns when prompted.
   - The program will generate a random matrix, print it, and determine its positive definiteness.

### Functions

#### `void create_matrix(MAT* mat, int rows, int cols)`

Allocates memory for a matrix with specified dimensions.

- `MAT* mat`: Pointer to the matrix structure.
- `int rows`: Number of rows.
- `int cols`: Number of columns.

#### `void free_matrix(MAT* mat)`

Frees the memory allocated for a matrix.

- `MAT* mat`: Pointer to the matrix structure.

#### `void print_matrix(MAT* mat)`

Prints the contents of a matrix to the console.

- `MAT* mat`: Pointer to the matrix structure.

#### `void populate_matrix_auto(MAT* mat)`

Fills the matrix with random values between -10 and 10.

- `MAT* mat`: Pointer to the matrix structure.

#### `char mat_test_positive_definiteness(MAT* mat)`

Tests if a matrix is positive definite using Cholesky decomposition.

- `MAT* mat`: Pointer to the matrix structure.
- **Returns**:
  - `MAT_POSDEF` (1): Positive definite
  - `MAT_POSSEMDEF` (2): Positive semidefinite
  - `MAT_NOTPOSDEF` (0): Not positive definite

### Example

```sh
Enter the number of rows for the matrix: 3
Enter the number of columns for the matrix: 3

Matrix A:
  5.000  -3.000   2.000 
 -3.000   5.000  -1.000 
  2.000  -1.000   3.000 

The matrix is positive definite
```
