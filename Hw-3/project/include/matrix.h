#ifndef PROJECT_INCLUDE_MATRIX_H_
#define PROJECT_INCLUDE_MATRIX_H_

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "math.h"

typedef struct Matrix {
    double** data;
    size_t rows_size;
    size_t cols_size;
} Matrix;

typedef enum MatrixErrType {
    CANT_OPEN_FILE = 0,
    CANT_READ_FSCANF,
    ROW_OR_COL_ZERO,
    CANT_MALLOC,
    NULL_POINTER,
    BORDER_EXIT,
    NOT_SAME_SIZE,
    NOT_SQUARE,
    NO_INVERSE_MATRIX
} MatrixErrType;

MatrixErrType get_err_code();

// Init/release operations
Matrix* create_matrix_from_file(const char* path_file);
Matrix* create_matrix(size_t rows, size_t cols);
int free_matrix(Matrix* matrix);

// Basic operations
int get_rows(const Matrix* matrix, size_t* rows);
int get_cols(const Matrix* matrix, size_t* cols);
int get_elem(const Matrix* matrix, size_t row, size_t col, double* val);
int set_elem(Matrix* matrix, size_t row, size_t col, double val);

// Math operations
Matrix* mul_scalar(const Matrix* matrix, double val);
Matrix* transp(const Matrix* matrix);

Matrix* sum(const Matrix* l, const Matrix* r);
Matrix* sub(const Matrix* l, const Matrix* r);
Matrix* mul(const Matrix* l, const Matrix* r);

// Extra operations
int det(const Matrix* matrix, double* val);
Matrix* adj(const Matrix* matrix);
Matrix* inv(const Matrix* matrix);
Matrix* minor(const Matrix* matrix, size_t size, size_t row, size_t col);

#endif  // PROJECT_INCLUDE_MATRIX_H_
