/**
 * @file vector.h
 * @brief This file contains the declaration of the Vector (m, 1)class .
 */

#ifndef VECTOR_H
#define VECTOR_H

#include "Matrix.h"



namespace phoenix{

/**
 *  @brief The Vector class represents a 1D matrix with generic programming.
 * 
 *  @tparam T Type of elements stored in the vector
 *  @tparam size Number of element in the vector
 */
template<typename T, int size>
class Vector : public Matrix<T, size, 1> {
 public:
        /**
     * @brief Constructs a vector object using matrix class constructor.
     *
     * @param list Initializer list for vector elements
     */
    Vector(std::initializer_list<T> list = {}) 
        : Matrix<T, size, 1>(list)
    {}

    /**
     * @brief Overloaded bracket operator to accesses vector element at index i.
     *
     * @param i row Row index of the element.
     *
     * @return T& Reference to the element at the specified index.
     */
    T& operator[] (int i)  {return Matrix<T, size, 1>::operator()(i, 0); }

    /**
     * @brief Overloaded bracket operator to accesses vector element at index i.
     *
     * @param i row Row index of the element.
     *
     * @return const T& Reference to the element at the specified index.
     */
    const T& operator[] (int i) const {return Matrix<T, size, 1>::operator()(i, 0); }

    // /**
    //  * @brief Multiplies the vector by a scalar value.
    //  *
    //  * @param scalar The scalar value to multiply the vector by.
    //  *
    //  * @return A reference to the current Vector object.
    //  */
    // Vector& operator*= (double scalar);


    // /**
    // * @brief Performs vector-matrix multiplication and returns the result as a new vector.
    // *
    // * @param v The vector to multiply.
    // * @param m The matrix to multiply.
    // *
    // * @return A new Vector object representing the result of the multiplication.
    // */
    // //Vector operator*(const Matrix& m);


    // /**
    //  * @brief Accesses an element of the vector at a given row.
    //  *
    //  * @param i The row of the element.
    //  *
    //  * @return A reference to the element at the specified row.
    //  */
    // double& operator[](int i);


    // /**
    //  * @brief Accesses an element of the vector at a given row.
    //  *
    //  * @param i The row of the element.
    //  *
    //  * @return A reference to the element at the specified row.
    //  */
    // const double& operator[](int i) const;


    // //vector multiply
    // void multiply(double scalar, Vector &t ); 

};

}



#endif