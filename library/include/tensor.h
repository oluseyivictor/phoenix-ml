/**
 * @file matrix.h
 * @brief This file contains the declaration of the Matrix class.
 */

#ifndef TENSOR_H
#define TENSOR_H


#include "Matrix.h"

using namespace phoenix;


template <typename T>
class Tensor {
public:
  Tensor();

  void addMatrix(const Matrix<T> &m);

  void print() {
    for (int i = 0; i<this->size(); i++)
    std::cout<<matrices_[i]<<std::endl;
    }

  Matrix<T>& operator[](int r) {return matrices_.at(r);}

  int size() {return matrices_.size();}



private:
  std::vector<Matrix<T>> matrices_;
};



template <typename T>
Tensor<T>::Tensor() {}

template <typename T>
void Tensor<T>::addMatrix(const Matrix<T> &m) {
  matrices_.push_back(m);

}


#endif