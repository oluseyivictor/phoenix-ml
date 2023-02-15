#include <iostream>
#include <gtest/gtest.h>
#include "Matrix.h"
#include "Vector.h"

using namespace phoenix; 

class MatrixTest : public ::testing::Test {
protected:
    Matrix<double>m1(2, 3);
    Matrix<double>m2(3, 2);

    virtual void SetUp() {
        m1(0, 0) = 1;
        m1(0, 1) = 2;
        m1(0, 2) = 3;
        m1(1, 0) = 4;
        m1(1, 1) = 5;
        m1(1, 2) = 6;

        m2 = {7,8,9,10,11,12};
    }
};

TEST_F(MatrixTest, Constructor) {
    EXPECT_EQ(m1.getRows(), 2);
    EXPECT_EQ(m1.getCols(), 3);
}

TEST_F(MatrixTest, IndexOperator) {
    m1(0, 0) = 1.0;
    m1(1, 2) = 2.5;
    EXPECT_EQ(m1(0, 0), 1.0);
    EXPECT_EQ(m1(1, 2), 2.5);
}

TEST_F(MatrixTest, Multiply) {
    Matrix<double> m3; 
    m3 = m1 * m2;
    EXPECT_EQ(m3.getRows(), 2);
    EXPECT_EQ(m3.getCols(), 2);
    EXPECT_EQ(m3(0, 0), 58);
    EXPECT_EQ(m3(0, 1), 64);
    EXPECT_EQ(m3(1, 0), 139);
    EXPECT_EQ(m3(1, 1), 154);
}

TEST_F(MatrixTest, Transpose) {
     Matrix<double> m3;
    m3 = m1.transpose();
    EXPECT_EQ(m3.getRows(), 3);
    EXPECT_EQ(m3.getCols(), 2);
    EXPECT_EQ(m3(0, 0), 1);
    EXPECT_EQ(m3(0, 1), 4);
    EXPECT_EQ(m3(1, 0), 2);
    EXPECT_EQ(m3(1, 1), 5);
    EXPECT_EQ(m3(2, 0), 3);
    EXPECT_EQ(m3(2, 1), 6);
}

class VectorTest : public ::testing::Test {
protected:
    Vector<double>  T1;
    Vector<double>  T2;

    virtual void SetUp() {
        T1[0] = 1;
        T1[1] = 2;
        T1[2] = 3;
        T1[3] = 4;
        T1[4] = 5;
        T1[5] = 6;


        T2 = {7,8,9,10,11,12};
    }
};

TEST_F(VectorTest, Constructor) {
    EXPECT_EQ(T1.getRows(), 6);
    EXPECT_EQ(T1.getCols(), 1);
}

TEST_F(VectorTest, IndexOperator) {
    T1[0] = 1.0;
    T2[2] = 2.5;
    EXPECT_EQ(T1[0], 2.0);
    EXPECT_EQ(T2[2], 2.5);
}

TEST_F(VectorTest, ScalerMultiply) {
    auto T3 = T1 * 3;
    EXPECT_EQ(T3[0], 3.0);
    EXPECT_EQ(T3[1], 6.0);
    EXPECT_EQ(T3[2], 9.0);
    EXPECT_EQ(T3[3], 12);
    EXPECT_EQ(T3[4], 15);
    EXPECT_EQ(T3[5], 18);

    T3 = 3 * T1;
    EXPECT_EQ(T3[0], 3.0);
    EXPECT_EQ(T3[1], 6.0);
    EXPECT_EQ(T3[2], 9.0);
    EXPECT_EQ(T3[3], 12);
    EXPECT_EQ(T3[4], 15);
    EXPECT_EQ(T3[5], 18);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
