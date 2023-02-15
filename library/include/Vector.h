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
template<typename T>
class Vector : public Matrix<T> {
    private:
    int v_size;
 public:
        /**
     * @brief Constructs a vector object using matrix class constructor.
     *
     * @param list Initializer list for vector elements
     */
    Vector(int size) 
        : Matrix<T>(size, 1)
    {
        v_size = size;
    }

    /**
     * @brief Overloaded bracket operator to accesses vector element at index i.
     *
     * @param i row Row index of the element.
     *
     * @return T& Reference to the element at the specified index.
     */
    T& operator[] (int i)  {return Matrix<T>::operator()(i, 0); }

    /**
     * @brief Overloaded bracket operator to accesses vector element at index i.
     *
     * @param i row Row index of the element.
     *
     * @return const T& Reference to the element at the specified index.
     */
    const T& operator[] (int i) const {return Matrix<T>::operator()(i, 0); }

    /**
     * @brief Multiplies the vector by a scalar value.
     *
     * @param scalar The scalar value to multiply the vector by.
     *
     * @return A reference to the current Vector object.
     */
    Vector<T> operator*(double scaler){
        Vector<T> result(v_size);
        for (int i = 0; i < v_size; i++){
            result[i] = (*this)[i]*scaler;
        }
        return result;
    }

    /**
     * @brief Multiplies the vector by a scalar value.
     *
     * @param scalar The scalar value to multiply the vector by.
     *
     * @return A reference to the current Vector object.
     */
    friend Vector<T> operator*(double scaler, const Vector<T>& other ){
        Vector<T> result(other.size());
        for (int i = 0; i < other.size(); i++){
            result[i] = other[i]*scaler;
        }
        return result;
    }


        void operator= (const std::initializer_list<T> list ) {
         int i = 0;
         //std::cout<<list.size()<<std::endl;
        for(const auto& value : list)
        {
           this->operator[](i++) = value;
            if (i== v_size) break;
        }
    }



    /**
    * @brief Performs vector-matrix multiplication and returns the result as a new vector.
    *
    * @param v The vector to multiply.
    * @param m The matrix to multiply.
    *
    * @return A new Vector object representing the result of the multiplication.
    */
   // Vector operator*(const Matrix& m);

};

}



#endif