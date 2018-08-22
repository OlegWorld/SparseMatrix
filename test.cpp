#include <gtest/gtest.h>
#include "sparsematrix.h"

TEST(SparseMatrixTest, TestEmptyMatrix) {
    Matrix<int, -1> matrix;
    EXPECT_EQ(matrix.size(), 0);
}

TEST(SparseMatrixTest, TestSingleCell) {
    Matrix<int, -1> matrix;
    auto a = matrix(0, 0);
    EXPECT_EQ(a, -1);
    EXPECT_EQ(matrix.size(), 0);
}

TEST(SparseMatrixTest, ModifyingCell) {
    Matrix<int, -1> matrix;
    matrix(100, 100) = 314;
    EXPECT_EQ(matrix(100, 100), 314);
    EXPECT_EQ(matrix.size(), 1);
}

TEST(SparseMatrixTest, ResetCell) {
    Matrix<int, -1> matrix;
    matrix(100, 100) = 314;
    EXPECT_EQ(matrix(100, 100), 314);
    EXPECT_EQ(matrix.size(), 1);
    matrix(100, 100) = -1;
    EXPECT_EQ(matrix(100, 100), -1);
    EXPECT_EQ(matrix.size(), 0);
}

TEST(SparseMatrixTest, TestValueGet) {
    Matrix<int, -1> matrix;
    matrix(100, 100) = 314;
    auto temp = matrix(100, 100).get();
    ::testing::StaticAssertTypeEq<decltype(temp), int>();
    EXPECT_EQ(temp, 314);
}

TEST(SparseMatrixTest, TestIterator) {
    Matrix<int, -1> matrix;
    matrix(100, 100) = 314;
    auto it = matrix.begin();
    size_t x, y;
    int v;
    std::tie(x, y, v) = *it;
    EXPECT_EQ(x, 100);
    EXPECT_EQ(y, 100);
    EXPECT_EQ(v, 314);
}

TEST(SparseMatrixTest, MultipleAssignmentTest) {
    Matrix<int, -1> matrix;
    ((matrix(100, 100) = 314) = 0) = 217;
    EXPECT_EQ(matrix(100, 100), 217);
    EXPECT_EQ(matrix.size(), 1);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}