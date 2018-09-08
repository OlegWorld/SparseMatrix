cmake_minimum_required(VERSION 3.5)
project(matrix)

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

install(TARGETS matrix RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_VERSION_PATCH "$ENV{TRAVIS_BUILD_NUMBER}")

set(CPACK_PACKAGE_CONTACT osmironov@gmail.com)

include(CPack)