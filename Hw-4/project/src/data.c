#include "data.h"

// data_t
data_t* init_data() {
    data_t* data = calloc(1, sizeof(data_t));
    if (!data) {
        return NULL;
    }

    for (int i = 0; i < 4; i++) {
        data->arr_data[i] = calloc(ALLOCATED_ONCE, sizeof(char));
        if (!data->arr_data[i]) {
            for (int j = 0; j < i; j++) {
                free(data->arr_data[j]);
            }
            free(data);

            return NULL;
        }

        data->arr_alloc[i] = ALLOCATED_ONCE;
    }

    data->part_count = 0;
    return data;
}

int realloc_data(data_t* data, int n, size_t pos) {
    if (!data) {
        return -1;
    }

    size_t alloc_twice = data->arr_alloc[pos] + n;

    char* new = realloc(data->arr_data[pos], alloc_twice * sizeof(char));
    if (!new) {
        return -1;
    }

    size_t strl = strlen(new);
    memset(new + strl, '\0', alloc_twice - strl);

    data->arr_alloc[pos] = alloc_twice;
    data->arr_data[pos] = new;

    return 0;
}

void free_data(data_t* data) {
    for (int i = 0; i < 4; i++) {
        if (data->arr_data[i]) {
            free(data->arr_data[i]);
        }
    }

    free(data);
}

int check_data_quotes(data_t* data) {
    if (!data) {
        return -1;
    }

    for (int i = 0; i < 4; i++) {
        size_t strl = strlen(data->arr_data[i]);
        if ((data->arr_data)[i][0]  == '\"' && (data->arr_data)[i][strl - 1] == '\"') {
            memmove(data->arr_data[i], data->arr_data[i] + 1, strl - 2);
            (data->arr_data)[i][strl - 2] = '\0';
            (data->arr_data)[i][strl - 1] = '\0';
        }
    }

    return 0;
}

int parser_print(data_t* data) {
    if (!data) {
        return -1;
    }

    for (int i = 0; i < 3; i++) {
        printf("%s|", data->arr_data[i]);
    }

    printf("%d", data->part_count);

    return 0;
}
