#include "data.h"

data_array_t* data_array_init() {
    data_array_t* data_init = (struct DataArray*)malloc(1 * sizeof(data_array_t));

    if (data_init == NULL) {
        return NULL;
    }

    data_init->data = (struct Data*)malloc((ALLOCATED_ONCE - 1) * sizeof(data_t));
    data_init->size = 0;
    data_init->allocated_size = ALLOCATED_ONCE;

    if (data_init->data == NULL) {
        free(data_init);
        return NULL;
    } else {
        return data_init;
    }
}

int data_array_add(data_array_t* data_current, data_t* data_add) {
    if (data_current == NULL) {
        return -1;
    }

    if (data_add == NULL) {
        return -1;
    }

    int size = data_current->size;
    int allocated_size = data_current->allocated_size;
    data_t* data_current_null = NULL;

    if (allocated_size == size) {
        allocated_size *= ALLOCATED_TWICE;
        data_current_null = (struct Data*)realloc(data_current->data, (allocated_size - 1) * sizeof(data_t));

        if (data_current_null == NULL) {
            return -1;
        }

        data_current->data = data_current_null;
    }

    data_current->data[size] = *data_add;
    data_current->size++;
    data_current->allocated_size = allocated_size;
    return 0;
}

void data_free(data_array_t* data_free) {
    if (data_free->data != NULL) {
        free(data_free->data);
    }

    if (data_free != NULL) {
        free(data_free);
    }
}
