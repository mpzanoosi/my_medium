# minimum required cmake
cmake_minimum_required(VERSION 3.9)

# project name
project(list)

# directories for outputs
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests)

# making list
set(CMAKE_C_FLAGS "-rdynamic -fPIC -g -Wformat")

# building test programs
add_executable(test_timing "test_timing.c")
add_executable(test_nested_list "test_nested_list.c")
add_executable(test_polymorphism "test_polymorphism.c")
add_executable(test_inheritance "test_inheritance.c")
