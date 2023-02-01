/**
 * @file matrix.h
 * @brief This file contains the declaration of the Matrix class.
 */

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <memory>
#include <cstdlib>
#include <initializer_list>
#include <vector>


namespace phoenix{


/**
 *  @brief The Matrix class represents a matrix of values with generic programming.
 * 
 *  @tparam T Type of elements stored in the matrix
 *  @tparam rows Number of rows in the matrix
 *  @tparam cols Number of cols in the matrix
 */

template<typename T, int rows, int cols>
class Matrix {

private:
    /**
     * @brief Unique pointer to the data stored in the matrix
     */
    std::shared_ptr<T[]> data;

public:
    /**
     * @brief Constructs a Matrix object with the specified number of rows and columns.
     *
     * @param list Initializer list for matrix elements
     */
    Matrix(std::initializer_list<T> list = {})
        : data(std::make_unique<T[]>(rows*cols))
    {
        int i = 0;
        for(const auto& value : list)
        {
            data[i++] = value;
            if (i== rows * cols) break;
        }
    }

    /**
     * @brief Get the number of rows in the matrix
     *
     * @return int Number of rows
     */
    int getRows() const {return rows;}


    /**
     * @brief Get the number of cols in the matrix
     *
     * @return int Number of cols
     */
    int getCols() const {return cols;}


    /**
     * @brief Overloaded parenthesis operator to accesses matrix element (mutable)).
     *
     * @param i row Row index of the element.
     * @param j col Column index of the element.
     *
     * @return T& Reference to the element at the specified row and column.
     */
    T& operator() (int i, int j) {return data[i * cols + j]; }


    /**
     * @brief Overloaded parenthesis operator to accesses matrix element(read-only)).
     *
     * @param i row Row index of the element.
     * @param j col Column index of the element.
     *
     * @return T& Reference to the element at the specified row and column.
     */
    const T& operator() (int i, int j) const {return data[i * cols + j]; }

    /**
     * @brief Accesses matrix element at the specified row and column(read-only)).
     *
     * @param i row Row index of the element.
     * @return A pointer to the first element in the row.
     */
    T* operator[](size_t row) {return data.get() + row * cols;}


    /**
     * @brief Accesses matrix element at the specified row and column(mutable)).
     *
     * @param i row Row index of the element.
     * @return A pointer to the first element in the row.
     */
    const T* operator[](size_t row) const {return data.get() + row * cols;}


    /**
     * @brief Get the total number of element in a matrix
     *
     * @return the total size of the matric given by row multiply by col
     */
    int size() const {return rows*cols;}

    T max(){
        T val = data[0];

        for (int i=1; i < size(); i++)
        {
            if(data[i] > val) val = data[i] ;
        }
        
        return val;
    }

    void randfill(){
        double d_rand;
        srand(2);

        for (int i=0; i < size(); i++){
            d_rand = (rand() % 10);
            d_rand /= 10;
            data[i] = d_rand;
        }
    }

    /**
     * @brief Multiplies two matrices and returns the result.
     *
     * @param other The matrix to multiply with.
     * @return The result of the matrix multiplication.
     */
    template<int col2>
    Matrix<T, rows, col2> operator*(const Matrix<T, cols, col2>& other) const{
    Matrix<T, rows, col2> result;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j< col2; j++){
            result[i][j] = 0;
            for (int k = 0; k < cols; k++) {
                result[i][j] += (*this)[i][k] * other[k][j];
            }
        }
    }
    return result;

}

    

    /**
     * @brief Multiplies two matrices and returns the result.
     *
     * @param other The matrix to multiply with.
     * @return The result of the matrix multiplication.
     */
    Matrix<T, cols, rows> transpose() const{
    Matrix<T, cols, rows> result;
    for (int i = 0; i< rows; i++){
        for (int j = 0; j < cols; j++){
            result[j][i] = operator()(i,j);
        }
    }
    return result;
}


     /**
     * @brief Overloaded stream operator to print the matrix
     *
     * @param os Output stream
     * @param mat Matrix to print
     * @return std::ostream& Output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Matrix<T, rows, cols>& mat){
    for (int i = 0; i<mat.getRows(); i++){
    for (int j = 0; j < mat.getCols(); j++){
        os<<mat.data[i * mat.getCols() + j]<<" ";
        }
        os<<std::endl;
    }   
    return os;
    }

    
};


template <typename T, int rows, int cols>
class Tensor {
public:
  Tensor();

  void addMatrix(const Matrix<T, rows, cols> &m);

  void print() {std::cout<<matrices_[0]<<std::endl;}

  Matrix<T, rows, cols> operator[](int r) {return matrices_.at(r);}

  int size() {return matrices_.size();}

private:
  std::vector<Matrix<T, rows, cols>> matrices_;
};



template <typename T, int rows, int cols>
Tensor<T, rows, cols>::Tensor() {}

template <typename T, int rows, int cols>
void Tensor<T, rows, cols>::addMatrix(const Matrix<T, rows, cols> &m) {
  matrices_.push_back(m);

}




}

#endif //MATRIX_H