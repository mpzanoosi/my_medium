# minimum required cmake
cmake_minimum_required(VERSION 3.9)

# project name
project(list)

# directories for outputs
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests)

# making list
set(CMAKE_C_FLAGS "-rdynamic -fPIC -g -Wformat")

# test ipc engine
add_executable(test_list "test_list.c")
