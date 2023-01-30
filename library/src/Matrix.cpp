/**
 * @file matrix.cpp
 * @brief This file contains the implementation of the Matrix class.
 */

#include "Matrix.h"

namespace phoenix{


Matrix::Matrix(int r, int c) : rows(r), cols(c) {
    data = new double*[rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new double[cols];
        }
    }



    Matrix::~Matrix() {
        for (int i = 0; i < rows; i++) {
            delete[] data[i];
        }
        delete[] data;
    }



    double& Matrix::operator() (int i, int j) const{
        return data[i][j];
    }



    void Matrix::operator<<(double *arr) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data[i][j] = arr[i*cols+j];
            }
        }
     
    }



    void Matrix::print() const{
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cout << operator()(i, j) << " ";
            }
            std::cout<<std::endl;
        }
    }
 

   int Matrix::size() const{
        return (rows*cols);
   }


}