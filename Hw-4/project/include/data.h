#ifndef PROJECT_INCLUDE_DATA_H_
#define PROJECT_INCLUDE_DATA_H_

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define ALLOCATED_ONCE 1

// data_t
typedef struct {
    char* arr_data[4];
    size_t arr_alloc[4];
    int part_count;
} data_t;

data_t* init_data();
int realloc_data(data_t* data, int n, size_t pos);
void free_data(data_t* data);
int check_data_quotes(data_t* data);
int parser_print(data_t* data);

#endif  // PROJECT_INCLUDE_DATA_H_
