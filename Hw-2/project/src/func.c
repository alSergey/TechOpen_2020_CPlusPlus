#include "func.h"

int add_new_data(const char* filename, file_type_t file_type) {
    if (filename == NULL) {
        return -1;
    }

    data_array_t* data_new = data_array_init();

    int continue_enter_data = 0;
    int i = 0;

    while (continue_enter_data != -1) {
        data_t data_add;
        int errs = 0;

        if (file_type == TRANSACTION_DATA) {
            printf("1 Number account: \n"
                   "2 Client cash payments: \n\n");

            errs = scanf("%3d %lf",
                  &data_add.number,
                  &data_add.cash_payments);

        } else {
            printf("1 Number account: \n"
                   "2 Client name: \n"
                   "3 Surname: \n"
                   "4 Addres client: \n"
                   "5 Client Telnum: \n"
                   "6 Client indebtedness: \n"
                   "7 Client credit limit: \n"
                   "8 Client cash payments: \n\n");

            errs = scanf("%12d%11s%11s%16s%20s%lf%lf%lf",
                  &data_add.number,
                  data_add.name,
                  data_add.surname,
                  data_add.addres,
                  data_add.tel_number,
                  &data_add.indebtedness,
                  &data_add.credit_limit,
                  &data_add.cash_payments);
        }

        if (errs == -1) {
            fprintf(stderr, "%s: impossible to scanf\n", filename);
            return -1;
        }

        int err = data_array_add(data_new, &data_add);
        i++;

        if (err == -1) {
            fprintf(stderr, "%s: no space for memory allocation\n", filename);
            return -1;
        }

        if (i == 2) {
            continue_enter_data = -1;
        }

       printf("\n");
    }

    int errw = write_to_file(filename, data_new, file_type);
    if (errw == -1) {
        fprintf(stderr, "%s: something wrong wit file (write)\n", filename);
    }

    data_free(data_new);
    return 0;
}


int black_record(const char* filename_first, const char* filename_second, const char* black_record) {
    if (filename_first == NULL) {
        return -1;
    }

    if (filename_second == NULL) {
        return -1;
    }

    if (black_record == NULL) {
        return -1;
    }

    data_array_t* data_first = NULL;
    int err_first = read_from_file(filename_first, &data_first, USER_DATA);

    if (err_first == -1) {
        fprintf(stderr, "%s: something wrong with file (read)\n", filename_first);
        data_free(data_first);
        return -1;
    }

    data_array_t* data_second = NULL;
    int err_second = read_from_file(filename_second, &data_second, TRANSACTION_DATA);

    if (err_second == -1) {
        fprintf(stderr, "%s: something wrong with file (read)\n", filename_second);
        data_free(data_first);
        data_free(data_second);
        return -1;
    }

    for (int i = 0; i < data_first->size; i++) {
        for (int j = 0; j < data_second->size; j++) {
            if (data_first->data[i].number == data_second->data[j].number
                    && data_second->data[j].cash_payments != 0) {
                data_first->data[i].credit_limit += data_second->data[j].cash_payments;
            }
        }
    }

    int errw = write_to_file(black_record, data_first, USER_DATA);

    if (errw == -1) {
        fprintf(stderr, "%s: something wrong wit file (write)\n", black_record);
        data_free(data_first);
        data_free(data_second);
        return -1;
    }

    data_free(data_first);
    data_free(data_second);
    return 0;
}
