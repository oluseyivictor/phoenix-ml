/**
 * @file nn.h
 * @brief lightweight neural network engine of phoenixs library .
 */

#ifndef UTILX_H
#define UTILX_H

#include "Matrix.h"
#include <algorithm>
#include <memory>
#include <random>
#include <initializer_list>

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

    template<typename T>
    Vector<T> mlayer_multiply(Vector<T>& input, Tensor<T>& weights){
        Vector<double>result(input.size());
        Matrix<T> fat = weights[0];
        result = vecTomat_multiply(input, fat);
        fat = weights[1];
        result = vecTomat_multiply(result, fat);

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
    Vector<T> v_sigmoid_derivative(Vector<T>& v) 
    {
        Vector<T>result(v.size());
    
        for (int i = 0; i < v.size(); i++)
        {
            result[i] =  sigmoid_derivative(v[i]);
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

template<typename T>
Matrix<T> SetMatrix(Matrix<T>& matrix, std::initializer_list<std::string> labels)
{
    int rows = matrix.getRows();
    int cols = labels.size();

    Matrix<T> result(rows, cols);
    
    int j = 0;
    for (std::string n : labels)
    {
        auto recept = convert_col(matrix, stoi(n));

        for (int i = 0; i < rows; i++)
        {
            result(i, j)= recept[i];
        }
    ++j;
    }
    
    return result;
}


template<typename T>
Matrix<T> RowMatrix(Matrix<T>& matrix, int nrows)
{
    int start = nrows > 0 ? 0 : abs(nrows) ;   // 0 (start) or 75(start) 
    int end  = nrows > 0 ? nrows : matrix.getRows() ; //35(end) or rows(end)


    std::cout<<start<<"    "<<end<<std::endl;

    int rows = end - start;
    int cols = matrix.getCols();

    Matrix<T> result(rows, cols);
    
    int j = 0; 
    for (int il = start; il < end; il++)
    {
        auto recept = convert_row(matrix, il);

        for (int i = 0; i < cols; i++)
        {
            result(j, i)= recept[i];
        }
    ++j;
    }
    
    return result;
}
template<typename T>
auto train_test_split(Matrix<T>& X, Matrix<T>& Y,float test_size =1.0)
{

    double train_no  = test_size;
    double test_no = (0 - test_size) ;

    test_no *= X.getRows() ;
    train_no *= Y.getRows();

    std::cout<<test_no<<"------"<<train_no<<std::endl;

    struct results {
        Matrix<T> X_train;
        Matrix<T> X_test;
        Matrix<T> Y_train;
        Matrix<T> Y_test;
    };

    return results{RowMatrix(X, train_no),
                   RowMatrix(X, test_no),
                   RowMatrix(Y, train_no),
                   RowMatrix(Y, test_no) };
    
}


#endif