#ifndef PROJECT_INCLUDE_DATA_H_
#define PROJECT_INCLUDE_DATA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALLOCATED_ONCE 5
#define ALLOCATED_TWICE 2

typedef struct Data {
    int number;
    char name[20];
    char surname[20];
    char addres[30];
    char tel_number[15];
    double indebtedness;
    double credit_limit;
    double cash_payments;
} data_t;

typedef struct DataArray {
    data_t* data;
    int size;
    int allocated_size;
} data_array_t;

typedef enum FileType {
    TRANSACTION_DATA,
    USER_DATA
} file_type_t;

data_array_t* data_array_init();
int data_array_add(data_array_t* data_current, data_t* data_add);
void data_free(data_array_t* data_free);

#endif  // PROJECT_INCLUDE_DATA_H_
