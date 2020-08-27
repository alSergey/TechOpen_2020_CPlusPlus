CMAKE_MINIMUM_REQUIRED(VERSION 3.14.0)

PROJECT(lec-6)

SET(CMAKE_CXX_STANDARD 17)

ADD_EXECUTABLE(1_global_operator_overload 1_global_operator_overload.cpp)

ADD_EXECUTABLE(2_copy_constructor 2_copy_constructor.cpp)
TARGET_COMPILE_OPTIONS(2_copy_constructor PRIVATE -O3)

ADD_EXECUTABLE(3_object_as_field 3_object_as_field.cpp)
