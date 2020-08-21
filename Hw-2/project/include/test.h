#ifndef PROJECT_INCLUDE_TEST_H_
#define PROJECT_INCLUDE_TEST_H_

#define READ_TEST_FILE "data_test_files/read_test.dat"
#define WRITE_TEST_FILE "data_test_files/write_test.dat"

#include <assert.h>
#include "func.h"

int test_write_to_file();
int is_compare(data_array_t* struct_first, data_array_t* struct_second);

#endif  // PROJECT_INCLUDE_TEST_H_
