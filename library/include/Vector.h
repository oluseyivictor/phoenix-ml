/**
 * @file vector.h
 * @brief This file contains the declaration of the Vector (m, 1)class .
 */

#ifndef VECTOR_H
#define VECTOR_H

#include "Matrix.h"



namespace gherkin{


/**
 * @brief The Vector class represents a vector of double values and inherits from the Matrix class.
 */
class Vector : public Matrix {
 public:
    /**
     * @brief Constructs a Vector object with the specified number of elements.
     *
     * @param n The number of elements in the vector.
     */
    Vector(int n) : Matrix(n, 1) {};


    /**
     * @brief Multiplies the vector by a scalar value.
     *
     * @param scalar The scalar value to multiply the vector by.
     *
     * @return A reference to the current Vector object.
     */
    Vector& operator*= (double scalar);


    /**
    * @brief Performs vector-matrix multiplication and returns the result as a new vector.
    *
    * @param v The vector to multiply.
    * @param m The matrix to multiply.
    *
    * @return A new Vector object representing the result of the multiplication.
    */
    //Vector operator*(const Matrix& m);


    /**
     * @brief Accesses an element of the vector at a given row.
     *
     * @param i The row of the element.
     *
     * @return A reference to the element at the specified row.
     */
    double& operator[](int i);


    /**
     * @brief Accesses an element of the vector at a given row.
     *
     * @param i The row of the element.
     *
     * @return A reference to the element at the specified row.
     */
    const double& operator[](int i) const;


    //vector multiply
    void multiply(double scalar, Vector &t ); 

};

}



#endif