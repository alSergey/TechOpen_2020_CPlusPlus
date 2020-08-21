#include "file.h"

int write_to_file(const char *filename, data_array_t* data_to_write, file_type_t file_type) {
    if (filename == NULL) {
        return -1;
    }

    if (data_to_write == NULL) {
        return -1;
    }

    FILE *file_to_write = fopen(filename, "w");

    if (file_to_write == NULL) {
        fprintf(stderr, "%s: not acess to write\n", filename);
        return -1;
    }

    for (int i = 0; i < data_to_write->size; i++) {
        data_t data_current = data_to_write->data[i];

        if (file_type == TRANSACTION_DATA) {
            fprintf(file_to_write, "%-3d%-6.2f\n",
                    data_current.number,
                    data_current.cash_payments);

        } else {
            fprintf(file_to_write, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
                    data_current.number,
                    data_current.name,
                    data_current.surname,
                    data_current.addres,
                    data_current.tel_number,
                    data_current.indebtedness,
                    data_current.credit_limit,
                    data_current.cash_payments);
        }
    }

    fclose(file_to_write);
    return 0;
}

int read_from_file(const char *filename, data_array_t** data_to_read, file_type_t file_type) {
    if (filename == NULL) {
        return -1;
    }

    if (data_to_read == NULL) {
        return -1;
    }

    FILE *file_to_read = fopen(filename, "r");

    if (file_to_read == NULL) {
        fprintf(stderr, "%s: not acess to read\n", filename);
        return -1;
    }

    *data_to_read = data_array_init();

    if (*data_to_read == NULL) {
        fprintf(stderr, "%s: no space for memory allocation\n", filename);
        fclose(file_to_read);
        return -1;
    }

    data_t* data_add = malloc(1 * sizeof(data_t));

    if (data_add == NULL) {
        fprintf(stderr, "%s: no space for memory allocation\n", filename);
        fclose(file_to_read);
        return 0;
    }

    while (!feof(file_to_read) && !ferror(file_to_read)) {
        int errs = 0;
        if (file_type == TRANSACTION_DATA) {
            errs = fscanf(file_to_read, "%3d %lf",
                &data_add->number,
                &data_add->cash_payments);

        } else {
            errs = fscanf(file_to_read, "%12d%11s%11s%16s%29s%lf%lf%lf",
                    &data_add->number,
                    data_add->name,
                    data_add->surname,
                    data_add->addres,
                    data_add->tel_number,
                    &data_add->indebtedness,
                    &data_add->credit_limit,
                    &data_add->cash_payments);
        }

        if (errs == -1) {
            free(data_add);
            fclose(file_to_read);
            return 0;
        }

        int err = data_array_add(*data_to_read, data_add);

        if (err == -1) {
            fprintf(stderr, "%s: no space for memory allocation\n", filename);
            fclose(file_to_read);
            return 1;
        }
    }

    free(data_add);
    fclose(file_to_read);
    return 0;
}
