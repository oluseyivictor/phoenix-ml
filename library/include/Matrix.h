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

template<typename T>
class Matrix {

public:
    /**
     * @brief Unique pointer to the data stored in the matrix
     */
    std::shared_ptr<T[]> data;
    int rows;
    int cols;

public:
    /**
     * @brief Constructs a Matrix object with the specified number of rows and columns.
     *
     * @param list Initializer list for matrix elements
     */
    Matrix(int r, int c = 1)
        : rows(r), cols(c),  data(std::make_unique<T[]>(r*c))    //can i make T[] STD::vector
        {

        }

    //virtual ~Matrix();


    /**
     * @brief Get the number of rows in the matrix
     *
     * @return int Number of rows
     */
    int getRows() const {return rows;}

    virtual void operator= (const std::vector<std::initializer_list<T>> list ) {
         int i = 0;
         //std::cout<<list.size()<<std::endl;
         for(const auto& val : list)
         {
        for(const auto& value : val)
        {
            data[i++] = value;
            if (i== rows * cols) break;
        }
         }
    }


    void insert(std::initializer_list<T> list ) {
         int i = 0;
         //std::cout<<list.size()<<std::endl;
        for(const auto& value : list)
        {
            data[i++] = value;
            if (i== rows * cols) break;
        }
        

    }
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

    double max(){
        double val = data[0];

        for (int i=1; i < size(); i++)
        {
            if(data[i] > val) val = data[i] ;
        }
        
        return val;
    }

    Matrix<T> scale() 
    {
        Matrix<T> result(rows, cols);
        T ran = this->max();
        //std::cout<<ran<<std::endl;
    
        for (int i = 0; i < this->size(); i++)
        {
            result.data[i] =  this->data[i]/ran;
        }
    
     return result;
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

    void zerofill(){
        double d_zero = 0;

        for (int i=0; i < size(); i++){

            data[i] = d_zero;
        }
    }    

    /**
     * @brief Multiplies two matrices and returns the result.
     *
     * @param other The matrix to multiply with.
     * @return The result of the matrix multiplication.
     */
    
    Matrix<T> operator*(const Matrix& other) const{
    Matrix<T> result;
    for (int i = 0; i < getRows(); i++){
        for (int j = 0; j< other.getCols(); j++){
            result[i][j] = 0;
            for (int k = 0; k < getCols(); k++) {
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
    Matrix<T> transpose() const{
    Matrix<T> result;
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
    friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& mat){
    for (int i = 0; i<mat.getRows(); i++){
    for (int j = 0; j < mat.getCols(); j++){
        os<<mat.data[i * mat.getCols() + j]<<" ";
        }
        os<<std::endl;
    }   
    return os;
    }

    
};


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



public:
  std::vector<Matrix<T>> matrices_;
};



template <typename T>
Tensor<T>::Tensor() {}

template <typename T>
void Tensor<T>::addMatrix(const Matrix<T> &m) {
  matrices_.push_back(m);

}




}

#endif //MATRIX_H