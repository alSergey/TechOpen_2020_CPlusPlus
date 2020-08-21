#include "matrix.h"

MatrixErrType err_code;
MatrixErrType get_err_code() {
    return err_code;
}

// Init/release operations
Matrix* create_matrix_from_file(const char* path_file) {
    FILE* open_file = fopen(path_file, "r");
    if (!open_file) {
        err_code = CANT_OPEN_FILE;
        return NULL;
    }

    size_t file_rows = 0, file_cols = 0;
    int err = fscanf(open_file, "%zu %zu\n", &file_rows, &file_cols);
    if (err != 2) {
        fclose(open_file);
        err_code = CANT_READ_FSCANF;
        return NULL;
    }
    if (file_rows == 0 || file_cols == 0) {
        fclose(open_file);
        err_code = ROW_OR_COL_ZERO;
        return NULL;
    }

    Matrix* current_matrix = create_matrix(file_rows, file_cols);
    if (!current_matrix) {
        fclose(open_file);
        err_code = CANT_MALLOC;
        return NULL;
    }

    for (size_t i = 0; i < file_rows; i++) {
        for (size_t j = 0; j < file_cols; j++) {
            err = fscanf(open_file, "%lf", &current_matrix->data[i][j]);
            if (err < 1) {
                free_matrix(current_matrix);
                fclose(open_file);
                err_code = CANT_READ_FSCANF;
                return NULL;
            }
        }
    }

    fclose(open_file);
    return current_matrix;
}

Matrix* create_matrix(size_t rows, size_t cols) {
    Matrix* current_matrix = malloc(sizeof(*current_matrix));
    if (!current_matrix) {
        err_code = CANT_MALLOC;
        return NULL;
    }

    current_matrix->rows_size = rows;
    current_matrix->cols_size = cols;

    current_matrix->data = malloc(rows * sizeof(*current_matrix->data));
    if (!current_matrix->data) {
        free_matrix(current_matrix);
        err_code = CANT_MALLOC;
        return NULL;
    }

    for (size_t i = 0; i < rows; i++) {
        current_matrix->data[i] = malloc(cols * sizeof(*current_matrix->data[i]));
        if (!current_matrix->data[i]) {
            free_matrix(current_matrix);
            err_code = CANT_MALLOC;
            return NULL;
        }
    }

    return current_matrix;
}

int free_matrix(Matrix* matrix) {
    if (!matrix) {
        err_code = NULL_POINTER;
        return -1;
    }

    for (size_t i = 0; i < matrix->rows_size; ++i) {
        if (matrix->data[i]) {
            free(matrix->data[i]);
        }
    }

    if (matrix->data) {
        free(matrix->data);
    }

    if (matrix) {
        free(matrix);
    }

    return 0;
}

// Basic operations
int get_rows(const Matrix* matrix, size_t* rows) {
    if (!matrix || !rows) {
        err_code = NULL_POINTER;
        return -1;
    }

    *rows = matrix->rows_size;
    return 0;
}

int get_cols(const Matrix* matrix, size_t* cols) {
    if (!matrix || !cols) {
        err_code = NULL_POINTER;
        return -1;
    }

    *cols = matrix->cols_size;
    return 0;
}

int get_elem(const Matrix* matrix, size_t row, size_t col, double* val) {
    if (!matrix || !val) {
        err_code = NULL_POINTER;
        return -1;
    }

    if ((row > matrix->rows_size - 1) || (col > matrix->cols_size - 1)) {
        err_code = BORDER_EXIT;
        return -1;
    }

    *val = matrix->data[row][col];
    return 0;
}

int set_elem(Matrix* matrix, size_t row, size_t col, double val) {
    if (!matrix) {
        err_code = NULL_POINTER;
        return -1;
    }

    if ((row > matrix->rows_size - 1) || (col > matrix->cols_size - 1)) {
        err_code = BORDER_EXIT;
        return -1;
    }

    matrix->data[row][col] = val;
    return 0;
}

// Math operations
Matrix* mul_scalar(const Matrix* matrix, double val) {
    if (!matrix) {
        err_code = NULL_POINTER;
        return NULL;
    }

    Matrix* result_matrix = create_matrix(matrix->rows_size, matrix->cols_size);
    if (!result_matrix) {
        err_code = CANT_MALLOC;
        return NULL;
    }

    for (size_t i = 0; i < matrix->rows_size; i++) {
        for (size_t j = 0; j < matrix->cols_size; j++) {
            result_matrix->data[i][j] = matrix->data[i][j] * val;
        }
    }

    return result_matrix;
}

Matrix* transp(const Matrix* matrix) {
    if (!matrix) {
        err_code = NULL_POINTER;
        return NULL;
    }

    Matrix* result_matrix = create_matrix(matrix->cols_size, matrix->rows_size);
    if (!result_matrix) {
        err_code = CANT_MALLOC;
        return NULL;
    }

    for (size_t i = 0; i < matrix->rows_size; i++) {
        for (size_t j = 0; j < matrix->cols_size; j++) {
            result_matrix->data[j][i] = matrix->data[i][j];
        }
    }

    return result_matrix;
}

Matrix* sum(const Matrix* l, const Matrix* r) {
    if (!l || !r) {
        err_code = NULL_POINTER;
        return NULL;
    }

    size_t size_row = l->rows_size;
    size_t size_col = l->cols_size;
    if (size_row != r->rows_size || size_col != r->cols_size) {
        err_code = NOT_SAME_SIZE;
        return NULL;
    }

    Matrix* result_matrix = create_matrix(size_row, size_col);
    if (!result_matrix) {
        err_code = CANT_MALLOC;
        return NULL;
    }

    for (size_t i = 0; i < size_row; i++) {
        for (size_t j = 0; j < size_col; j++) {
            result_matrix->data[i][j] = l->data[i][j] + r->data[i][j];
        }
    }

    return result_matrix;
}

Matrix* sub(const Matrix* l, const Matrix* r) {
    if (!l || !r) {
        err_code = NULL_POINTER;
        return NULL;
    }

    size_t size_row = l->rows_size;
    size_t size_col = l->cols_size;
    if (size_row != r->rows_size || size_col != r->cols_size) {
        err_code = NOT_SAME_SIZE;
        return NULL;
    }

    Matrix* result_matrix = create_matrix(size_row, size_col);
    if (!result_matrix) {
        err_code = CANT_MALLOC;
        return NULL;
    }

    for (size_t i = 0; i < size_row; i++) {
        for (size_t j = 0; j < size_col; j++) {
            result_matrix->data[i][j] = l->data[i][j] - r->data[i][j];
        }
    }

    return result_matrix;
}


Matrix* mul(const Matrix* l, const Matrix* r) {
    if (!l || !r) {
        err_code = NULL_POINTER;
        return NULL;
    }

    if (l->cols_size != r->rows_size) {
        err_code = NOT_SQUARE;
        return NULL;
    }

    Matrix* result_matrix = create_matrix(l->rows_size, r->cols_size);
    if (!result_matrix) {
        err_code = CANT_MALLOC;
        return NULL;
    }

    for (size_t i = 0; i < l->rows_size; i++) {
        for (size_t j = 0; j < r->cols_size; j++) {
            result_matrix->data[i][j] = 0;
        }
    }

    for (size_t i = 0; i < l->rows_size; i++) {
        for (size_t j = 0; j < r->cols_size; j++) {
            for (size_t k = 0; k < l->cols_size; k++) {
                result_matrix->data[i][j] += l->data[i][k] * r->data[k][j];
            }
        }
    }

    return result_matrix;
}

// Extra operations
int det(const Matrix* matrix, double* val) {
    if (!matrix) {
        err_code = NULL_POINTER;
        return -1;
    }

    if (matrix->rows_size != matrix->cols_size) {
        err_code = NOT_SQUARE;
        return -1;
    }

    size_t size = matrix->rows_size;

    if (size == 1) {
        *val = matrix->data[0][0];
        return 0;
    }

    if (size == 2) {
        *val = matrix->data[0][0] * matrix->data[1][1] - matrix->data[0][1] * matrix->data[1][0];
        return 0;
    }

    double deter = 0;
    int degree = 1;

    for (size_t i = 0; i < size; i++) {
        Matrix* new_matrix = minor(matrix, size, 0, i);
        if (!new_matrix) {
            err_code = CANT_MALLOC;
            return -1;
        }

        double new_val = 0;
        det(new_matrix, &new_val);

        deter += degree * matrix->data[0][i] * (new_val);
        degree = -degree;

        free_matrix(new_matrix);
    }

    *val = deter;
    return 0;
}

Matrix* adj(const Matrix* matrix) {
    if (!matrix) {
        err_code = NULL_POINTER;
        return NULL;
    }

    if (matrix->rows_size != matrix->cols_size) {
        err_code = NOT_SQUARE;
        return NULL;
    }

    size_t size = matrix->rows_size;

    Matrix* result_matrix = create_matrix(size, size);
    if (!result_matrix) {
        err_code = CANT_MALLOC;
        return NULL;
    }

    if (size == 1) {
        result_matrix->data[0][0] = 1;
        return result_matrix;
    }

    Matrix* transp_matrix = transp(matrix);
        if (!transp_matrix) {
            err_code = CANT_MALLOC;
            return NULL;
        }

    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            Matrix* minor_matrix = minor(transp_matrix, size, i, j);
            if (!minor_matrix) {
                free_matrix(transp_matrix);
                err_code = CANT_MALLOC;
                return NULL;
            }

            double val = 0;
            det(minor_matrix, &val);

            result_matrix->data[i][j] = pow(-1, i + j) * (val);
            free_matrix(minor_matrix);
        }
    }

    free_matrix(transp_matrix);
    return result_matrix;
}

Matrix* inv(const Matrix* matrix) {
    if (!matrix) {
        err_code = NULL_POINTER;
        return NULL;
    }

    if (matrix->rows_size != matrix->cols_size) {
        err_code = NOT_SQUARE;
        return NULL;
    }

    double val = 0;
    det(matrix, &val);
    if (val == 0) {
        err_code = NO_INVERSE_MATRIX;
        return NULL;
    }
    val = 1/(val);

    Matrix* adj_matrix = adj(matrix);
    if (!adj_matrix) {
        err_code = CANT_MALLOC;
        return NULL;
    }

    Matrix* result_matrix = mul_scalar(adj_matrix, val);
    if (!result_matrix) {
        free_matrix(adj_matrix);
        err_code = CANT_MALLOC;
        return NULL;
    }

    free_matrix(adj_matrix);
    return result_matrix;
}

Matrix* minor(const Matrix* matrix, size_t size, size_t row, size_t col) {
    if (!matrix) {
        err_code = NULL_POINTER;
        return NULL;
    }

    Matrix* new_matrix = create_matrix(size - 1, size -1);
    if (!new_matrix) {
        err_code = CANT_MALLOC;
        return NULL;
    }

    int offset_row = 0;

    for (size_t i = 0; i < size - 1; i++) {
        if (i == row) {
            offset_row = 1;
        }

        int offset_col = 0;

        for (size_t j = 0; j < size-1; j++) {
            if (j == col) {
                offset_col = 1;
            }

            new_matrix->data[i][j] = matrix->data[i + offset_row][j + offset_col];
        }
    }

    return new_matrix;
}
