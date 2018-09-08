#include <iostream>
#include <cassert>
#include "sparsematrix.h"

int main() {
    Matrix<int, 0> matrix;
    for(size_t i = 0, j = 9; i < 10; i++, j--) {
        matrix(i, i) = i;
        matrix(i, j) = j;
    }

    print_submatrix(matrix, 1, 1, 8, 8);

    std::cout << "Used cells number: " << matrix.size() << std::endl;

    print_cells(matrix);

    return 0;
}