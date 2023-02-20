/**
 * @file vector.h
 * @brief This file contains the declaration of the Vector (m, 1)class .
 */

#ifndef VECTOR_H
#define VECTOR_H

#include "Matrix.h"
#include <cmath>


double rms_error(double y_pred, double y_true) {return 0.5 * pow((y_pred - y_true), 2);}
double pd_error(const double a, const double b) { return a - b; }

    double sigmoid(double x){
        double result;
        result = 1/(1 + std::exp(-x));

        return result;
    }

 
double sigmoid_derivative(double a){
        double result;
        result = sigmoid(a) * (1.0 - sigmoid(a));

        return result;
    }   
    
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
    T& operator[] (int i)  {
        if (i > v_size) {
            throw std::invalid_argument("Accessing wrong parameter in vector. ");
        }
        return Matrix<T>::operator()(i, 0); 
        }

    /**
     * @brief Overloaded bracket operator to accesses vector element at index i.
     *
     * @param i row Row index of the element.
     *
     * @return const T& Reference to the element at the specified index.
     */
    const T& operator[] (int i) const {
        if (i > v_size) {
            throw std::invalid_argument("Accessing wrong parameter in vector. ");
        }
        return Matrix<T>::operator()(i, 0); }

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

    friend Vector<T> operator-(const Vector& target, const Vector& out) 
    {
        if (out.getRows() != target.getRows()) {
            throw std::invalid_argument("The number of vector rows must be equal in vector error. ");
        }

        Vector<T> result(out.size());

        double sum = 0;
        for (int i=0; i < out.size(); i++){
            result[i] = (target[i] - out[i]) * sigmoid_derivative(out[i]);
        }

        return result;
    }


    friend Vector<T> operator+(const Vector& v, const Vector& other) 
    {
        if (v.getRows() != other.getRows()) {
            throw std::invalid_argument("The number of vector rows must be equal in vector + error. ");
        }

        Vector<T> result(other.size());
    
        for (int i=0; i < v.size(); i++){
            result[i] = v[i] + other[i];
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

    friend Vector<T> operator*(const Vector<T>& other, double scaler){
        Vector<T> result(other.size());
        result = (scaler * other);
        return result;
    }

    friend Vector<T> operator*(Matrix<T>& m2, const Vector<T>& v1){
        if (v1.getRows() != m2.getCols()) {
            throw std::invalid_argument("The number of vector rows must be equal to Matrix column. ");
        }
        
        Vector<double>result(m2.getRows()); 

        for (int k = 0; k < m2.getRows(); k++){
            
            result[k] = 0;

            for (int i = 0; i < v1.getRows(); i++){

                result[k] += v1[i]  * m2[k][i];

            }
      // std::cout<< "...Result... = "<< result[k]<<std::endl;
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