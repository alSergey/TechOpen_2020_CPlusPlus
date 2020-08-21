#include "matrix.h"

int main(void) {
    char* left_filename = "left.txt";
    char* right_filename = "right.txt";

    Matrix* left_matrix = create_matrix_from_file(left_filename);
    if (!left_matrix) {
        printf("Error code: %d\n", get_err_code());
        return -1;
    }

    Matrix* right_matrix = create_matrix_from_file(right_filename);
    if (!right_matrix) {
        free_matrix(left_matrix);
        printf("Error code: %d\n", get_err_code());
        return -1;
    }

    // Basic operations
    int err = 0;
    size_t a = 0;
    double b = 0;

    err = get_rows(left_matrix, &a);
    if (err == -1) {
        free_matrix(left_matrix);
        free_matrix(right_matrix);
        printf("Error code: %d\n", get_err_code());
        return -1;
    }
    printf("Row size: %zu\n", a);

    err = get_cols(left_matrix, &a);
    if (err == -1) {
        free_matrix(left_matrix);
        free_matrix(right_matrix);
        printf("Error code: %d\n", get_err_code());
        return -1;
    }
    printf("Col size: %zu\n", a);

    err = get_elem(right_matrix, 1, 1, &b);
    if (err == -1) {
        free_matrix(left_matrix);
        free_matrix(right_matrix);
        printf("Error code: %d\n", get_err_code());
        return -1;
    }
    printf("Element 1 1: %.2f\n", b);

    err = set_elem(right_matrix, 0, 0, b);
    if (err == -1) {
        free_matrix(left_matrix);
        free_matrix(right_matrix);
        printf("Error code: %d\n", get_err_code());
        return -1;
    }

    // Math operations
    Matrix* sum_matrix = sum(left_matrix, right_matrix);
    if (!sum_matrix) {
        free_matrix(left_matrix);
        free_matrix(right_matrix);
        printf("Error code: %d\n", get_err_code());
        return -1;
    }
    free_matrix(sum_matrix);

    Matrix* sub_matrix = sub(left_matrix, right_matrix);
    if (!sub_matrix) {
        free_matrix(left_matrix);
        free_matrix(right_matrix);
        printf("Error code: %d\n", get_err_code());
        return -1;
    }
    free_matrix(sub_matrix);

    Matrix* mul_matrix = mul(left_matrix, right_matrix);
    if (!mul_matrix) {
        free_matrix(left_matrix);
        free_matrix(right_matrix);
        printf("Error code: %d\n", get_err_code());
        return -1;
    }
    free_matrix(mul_matrix);

    // Extra operations
    Matrix* inv_matrix = inv(left_matrix);
    if (!inv_matrix) {
        free_matrix(left_matrix);
        free_matrix(right_matrix);
        printf("Error code: %d\n", get_err_code());
        return -1;
    }
    free_matrix(inv_matrix);

    free_matrix(left_matrix);
    free_matrix(right_matrix);
    return 0;
}

