#include "test.h"

int test_write_to_file() {
    data_array_t* data_test_first = NULL;
    int err_first = read_from_file(READ_TEST_FILE, &data_test_first, USER_DATA);

    if (err_first == -1) {
        fprintf(stderr, "%s: something wrong wit file (read)\n", READ_TEST_FILE);
        data_free(data_test_first);
        return -1;
    }

    int errw_first = write_to_file(WRITE_TEST_FILE, data_test_first, USER_DATA);

    if (errw_first == -1) {
        fprintf(stderr, "%s: something wrong wit file (write)\n", WRITE_TEST_FILE);
        data_free(data_test_first);
        return -1;
    }

    data_array_t* data_test_second = NULL;
    int err_second = read_from_file(WRITE_TEST_FILE, &data_test_second, USER_DATA);

    if (err_second == -1) {
        fprintf(stderr, "%s: something wrong wit file (read)\n", WRITE_TEST_FILE);
        data_free(data_test_first);
        data_free(data_test_second);
        return -1;
    }

    int err = 1;
    if (is_compare(data_test_first, data_test_second) == -1) {
        err = 0;
    }

    assert(err != 0);
    data_free(data_test_first);
    data_free(data_test_second);
    return 0;
}

int is_compare(data_array_t* struct_first, data_array_t* struct_second) {
    if (struct_first->size == struct_second->size) {
        int compare = 0;
        for (int i = 0; i < struct_first->size; i++) {
            if (struct_first->data[i].number != struct_second->data[i].number) {
                return -1;
            }

            if (strcmp(struct_first->data[i].name, struct_second->data[i].name) != 0) {
                return -1;
            }

            if (strcmp(struct_first->data[i].surname, struct_second->data[i].surname) != 0) {
                return -1;
            }

            if (strcmp(struct_first->data[i].addres, struct_second->data[i].addres) != 0) {
                return -1;
            }

            if (strcmp(struct_first->data[i].tel_number, struct_second->data[i].tel_number) != 0) {
                return -1;
            }

            if (struct_first->data[i].indebtedness != struct_second->data[i].indebtedness) {
                return -1;
            }

            if (struct_first->data[i].credit_limit != struct_second->data[i].credit_limit) {
                return -1;
            }

            if (struct_first->data[i].cash_payments != struct_second->data[i].cash_payments) {
                return -1;
            }
            compare++;
        }

        if (compare == struct_first->size) {
            return 0;
        } else {
            return -1;
        }

    } else {
        return -1;
    }
}
