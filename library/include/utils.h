/**
 * @file nn.h
 * @brief lightweight neural network engine of phoenixs library .
 */

#ifndef UTILX_H
#define UTILX_H

#include "Vector.h"
#include <algorithm>
#include <memory>
#include <random>
#include <cmath>

using namespace phoenix;

    /**
     * @brief Single input single output neural network.
     *
     * @param input The value of the input element.
     * @param weight The weight attached with the input.
     *
     * @return A predicted value which is input multiplied by weight.
     */
    double scalar_multiply(double input, double weight) { return(input*weight); }

    double square_error(double y_pred, double y_true) {return pow((y_pred - y_true), 2);}

    template<typename T>
     Vector<T> convert_row(Matrix<T>& other, int i)
    {
        Vector<T> result(other.getCols());
        for (int j = 0; j < other.getCols(); j++)
        {
            result[j] =  other(i, j);
        }
        
        return result;

    }

    template<typename T>
     Vector<T> convert_col(Matrix<T>& other, int j)
    {
        Vector<T> result(other.getRows());
        for (int i = 0; i < other.getRows(); i++)
        {
            result[i] =  other(i, j);
        }
        
        return result;

    }

    template<typename T>
    T vecTovec_multiply(const Vector<T>& input, const Vector<T>& weight){      //vector to vector multiply

       T output = 0;

      for(int i = 0; i < input.getRows(); i++){

         output += input[i]*weight[i];

        }
        return output;
    }


    template<typename T>
    Vector<T> vecTomat_multiply(Vector<T>& v1, Matrix<T>& m2){          //vector to matrixmultiply
        Vector<double>result(m2.getRows()); 

        for (int k = 0; k < m2.getRows(); k++){

            for (int i = 0; i < v1.getRows(); i++){

                result[k] += v1[i]  * m2[k][i];

            }
      // std::cout<< "...Result... = "<< result[k]<<std::endl;
        }
         
        
        return result;
    }

    template<typename T>
    Vector<T> mlayer_multiply(Vector<T>& input, Tensor<T>& weights){
        Vector<double>result(input.size());
        Matrix<T> fat = weights[0];
        result = vecTomat_multiply(input, fat);
        fat = weights[1];
        result = vecTomat_multiply(result, fat);

        return result;
    }

    double sigmoid(double x){
        double result;
        result = 1/(1 + exp(-x));

        return result;
    }
    
    template<typename T>
    Vector<T> vector_sigmoid(Vector<T>& v) 
    {
        Vector<T>result(v.size());
    
        for (int i = 0; i < v.size(); i++)
        {
            result[i] =  sigmoid(v[i]);
        }
    
     return result;
    }

template<typename T>
void ShuffleMatrixRows(Matrix<T>& matrix, double randomness = 1.0) {
  std::mt19937 rng(std::random_device{}());
  std::uniform_real_distribution<double> dist(0, 1);

  for (int i = 0; i < matrix.getRows(); ++i) {
    if (dist(rng) <= randomness) {
      int j = i + std::uniform_int_distribution<int>(0, matrix.getRows() - i - 1)(rng);
      std::swap_ranges(matrix.data.get() + i * matrix.getCols(),
                       matrix.data.get() + (i + 1) * matrix.getCols(),
                       matrix.data.get() + j * matrix.getCols() );
    }
  }
}


#endif