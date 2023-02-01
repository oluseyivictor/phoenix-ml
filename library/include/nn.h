/**
 * @file nn.h
 * @brief lightweight neural network engine of phoenixs library .
 */

#ifndef NN_H
#define NN_H

#include "Vector.h"
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

    template<typename T, int rows, int cols>
    Vector<T, cols> convert(Matrix<T, rows, cols>& other, int i)
    {
        Vector<T, cols> result;
        for (int j = 0; j < cols; j++)
        {
            result[j] =  other(i, j);
        }
        
        return result;

    }


    template<typename T, int size>
    T weighted_sum(const Vector<T, size>& input, const Vector<T, size>& weight){

       T output = 0;

      for(int i = 0; i < size; i++){

         output += input[i]*weight[i];

        }
        return output;
    }


    template<typename T, int size, int row, int col>
    Vector<T, size> vecTomat_multiply(Vector<T, size>& v1, Matrix<T, row, col>& m2){
        Vector<double, size>  result;
        for (int i = 0; i < size; i++){
        result[i] = weighted_sum( v1, convert(m2, i));
        }
        return result;
    }

    template<typename T, int size, int row, int col>
    Vector<T, size> mlayer_multiply(Vector<T, size>& input, Tensor<T, row, col>& weights){
        Vector<double, size>  result;
        Matrix<T, row, col> fat = weights[0];
        result = vecTomat_multiply(input, fat);
        fat = weights[1];
        result = vecTomat_multiply(result, fat);

        return result;
    }


    

class Model {


public:
    /**
     * @brief Constructs a neural network model object.
     */
    Model() {};


    /**
     * @brief Destructs a neural network model.
     */
    ~Model() {};


    


};




#endif