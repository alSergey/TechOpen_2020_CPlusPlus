#ifndef PROJECT_INCLUDE_FUNC_H_
#define PROJECT_INCLUDE_FUNC_H_

#include "file.h"

int add_new_data(const char* filename, file_type_t file_type);
int black_record(const char* filename_first, const char* filename_second, const char* blackrecord);

#endif  // PROJECT_INCLUDE_FUNC_H_
