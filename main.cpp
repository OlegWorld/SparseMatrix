#include <iostream>
#include <cassert>
#include "sparsematrix.h"

int main() {
//    Matrix<int, -1> matrix;
//    assert(matrix.size() == 0);
//
//    auto a = matrix(0, 0);
//    assert(a == -1);
//    assert(matrix.size() == 0);
//
//    matrix(100, 100) = 314;
//    assert(matrix(100, 100) == 314);
//    assert(matrix.size() == 1);
//
//    for(auto c : matrix)
//    {
//        int x;
//        int y;
//        int v;
//        std::tie(x, y, v) = c;
//        std::cout << x << y << v << std::endl;
//    }

    Matrix<int, 0> matrix;
    for(size_t i = 0, j = 9; i < 10; i++, j--) {
        matrix(i, i) = i;
        matrix(i, j) = j;
    }

    print_submatrix(matrix, 1, 1, 8, 8);

    std::cout << "Used cells number: " << matrix.size() << std::endl;

    for (const auto& c : matrix)
    {
        size_t x, y;
        int v;
        std::tie(x, y, v) = c;
        std::cout << "matrix(" << x << ", " << y << ") = " << v << std::endl;
    }

    return 0;
}