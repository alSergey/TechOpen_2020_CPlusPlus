#ifndef PROJECT_INCLUDE_FILE_H_
#define PROJECT_INCLUDE_FILE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

#define TRANSATION_FILE "transaction.dat"
#define RECORD_FILE "record.dat"
#define BLACKRECORD_FILE "blackrecord.dat"

int write_to_file(const char* filename, data_array_t* data_to_write, file_type_t file_type);
int read_from_file(const char* filename, data_array_t** data_to_read, file_type_t file_type);

#endif  // PROJECT_INCLUDE_FILE_H_
