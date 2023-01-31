/**
 * @file matrix.h
 * @brief This file contains the declaration of the Matrix class.
 */

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <memory>
#include <initializer_list>


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
    std::unique_ptr<T[]> data;

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
     * @brief Overloaded parenthesis operator to accesses matrix element at a given row and column.
     *
     * @param i row Row index of the element.
     * @param j col Column index of the element.
     *
     * @return T& Reference to the element at the specified row and column.
     */
    T& operator() (int i, int j) const {return data[i * cols + j]; };


    /**
     * @brief Get the total number of element in a matrix
     *
     * @return the total size of the matric given by row multiply by col
     */
    int size() const {return rows*cols;}

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

}

#endif //MATRIX_H