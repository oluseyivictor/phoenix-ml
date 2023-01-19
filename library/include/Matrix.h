/**
 * @file matrix.h
 * @brief This file contains the declaration of the Matrix class.
 */

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>


namespace gherkin{
/**
 * @brief The Matrix class represents a matrix of double values.
 */
class Matrix {
private:
    /**
     * @brief The number of rows in the matrix.
     */
    int rows;
    /**
     * @brief The number of columns in the matrix.
     */
    int cols;

protected:
    /**
     * @brief A 2D array of double values representing the matrix.
     */
    double** data;

public:
    /**
     * @brief Constructs a Matrix object with the specified number of rows and columns.
     *
     * @param rows The number of rows in the matrix.
     * @param cols The number of columns in the matrix.
     */
    Matrix(int rows, int cols);

    /**
     * @brief Destructs a Matrix object and frees up memory.
     */
    ~Matrix();


    /**
     * @brief Accesses an element of the matrix at a given row.
     *
     * @return A reference to the element at the specified row.
     */
    int row() const {return rows;}


    /**
     * @brief Accesses an element of the matrix at a given column.
     *
     * @return A reference to the element at the specified column.
     */
    int col() const {return cols;}


    /**
     * @brief Accesses an element of the matrix at a given row and column.
     *
     * @param irow The row of the element.
     * @param jcol The column of the element.
     *
     * @return A reference to the element at the specified row and column.
     */
    double& operator() (int irow, int jcol) const;

    /**
     * @brief maps an array into element of the matrix at a given row and column.
     *
     * @param arr an array element of size n.
     */
    void operator<<(double *arr);


    /**
     * @brief the content of matrix are printed on screen
     *
     * @return the total size of the matric given by row multiply by col
     */
    int size() const;


    /**
     * @brief the content of matrix are printed on screen
     *
     */
    void print() const;


    
};

}

#endif //MATRIX_H