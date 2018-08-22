cmake_minimum_required(VERSION 3.7)
project(SparseMatrix)

find_package(GTest REQUIRED)
find_package (Threads REQUIRED)

add_executable(matrix main.cpp sparsematrix.h)

add_executable(SparseMatrixTest test.cpp)

target_include_directories(SparseMatrixTest PRIVATE ${GTEST_INCLUDE_DIRS})

set_target_properties(matrix PROPERTIES     CXX_STANDARD 14
                                            CXX_STANDARD_REQUIRED ON
                                            COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra;-Werror")

set_target_properties(SparseMatrixTest PROPERTIES   CXX_STANDARD 14
                                                    CXX_STANDARD_REQUIRED ON)

target_link_libraries(SparseMatrixTest ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_test(test SparseMatrixTest)

enable_testing()