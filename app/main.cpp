#include <iostream>
#include "config.hpp"
#include "nn.h"
#include "Vector.h"
#include <nlohmann/json.hpp>



 template<typename T, int rows, int cols>
Vector<T, cols> convert(Matrix<T, rows, cols>& other, int i);

using namespace phoenix;



int main(){

Model pred;

Matrix<double, 3, 3> weights1({-2.0, 9.5, 2.01,
                               -0.8, 7.2, 6.3,
                               -0.5, 0.45, 0.9});

Matrix<double, 3, 3> weights2({ -1.0,   1.15,  0.11,
                                -0.18,  0.15, -0.01,
                                 0.25, -0.25, -0.1});

Matrix<double, 3, 3> weights3;

weights3.randfill();

Tensor<double, 3, 3> debate;
debate.addMatrix(weights1);
debate.addMatrix(weights2);

double expected_val[3] = {600, 10, -90};

// debate.push_back(weights);

Vector<double, 3> inputs({30, 87, 110});

Vector<double, 3> newData({12, 60, 60});
Vector<double, 3>  nData({-2, 2, 1});

Vector<double, 3> out;

 //out = vecTomat_multiply(inputs, weights3);
//out = mlayer_multiply(inputs, debate);
out.randfill();

 //double base = weighted_sum(newData, nData);    //156

auto rand = inputs.scale() ;


std::cout<< rand <<std::endl;
    
   std::cout<< weights3<<std::endl;
     std::cout<< out<<std::endl;
// std::cout<< square_error(expected_val[2], out[2])<<std::endl;

    return 1;
}