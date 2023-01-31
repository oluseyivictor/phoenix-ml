#include <iostream>
#include "config.hpp"
#include "nn.h"
#include "Vector.h"
#include <nlohmann/json.hpp>



using namespace phoenix;

int main(){

Model pred;

Matrix<int,2,3> poo;

Vector<double, 5> newData({9,2,3,8,5});
Vector<double, 5>  nData({1,2.3,3.6,4.6,9.5});

Matrix<float, 3, 3> mat({1,3,5,
                         4,5,6,
                         7,8,9});

Matrix<int, 2, 3> m1;
Matrix<int, 3, 2> m2;


        m1(0, 0) = 1;
        m1(0, 1) = 2;
        m1(0, 2) = 3;
        m1(1, 0) = 4;
        m1(1, 1) = 5;
        m1(1, 2) = 6;

        m2(0, 0) = 7;
        m2(0, 1) = 8;
        m2(1, 0) = 9;
        m2(1, 1) = 10;
        m2(2, 0) = 11;
        m2(2, 1) = 12;

Matrix<int, 2, 2> m3 = m1 * m2;

 std::cout<< m3<<std::endl;
 //mat2 = mat.transpose();


// std::cout<< mat2<<std::endl;

  std::cout<< newData[2]<<std::endl;

Vector<double, 5>  lData;

lData = nData * 2.8;

 std::cout<< lData<<std::endl;

 lData = 2.8 * nData;

// int base = pred.weighted_sum(lData, nData);
//   std::cout<< base<<std::endl;

double base = pred.single_nn(nData[2], mat[1][2]);
  std::cout<< base<<std::endl;

    return 1;
}