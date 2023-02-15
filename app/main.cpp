#include <iostream>
#include "config.hpp"
#include "io.h"
#include "utils.h"
#include "Matrix.h"
#include "Vector.h"
#include <nlohmann/json.hpp>

using namespace phoenix;

int main() {


Matrix<double>raw_X(3,2);

 ReadFileToMatrix("../../app/data.txt", raw_X);
// raw_X =Matrix<double>(3,34);

//raw_X = {{2, 8},{5, 5},{1, 8}};                                                 

Matrix<double> raw_Y(3);    //Matrix<double> raw_Y(3);  raw_Y = {200, 90, 100};
Matrix<double> raw_Z(3); 
//raw_Y = {{200, 90, 100}};

//auto train_X = raw_X.scale();
//auto train_Y = raw_Y.scale();

//std::cout<< raw_X  <<std::endl;

//ShuffleMatrixRows(raw_X);

//auto Tr = convert_col(raw_X, 7);

//std::cout<< Tr <<std::endl;



raw_Y = SetMatrix(raw_X, {"0","1","2","3","4"});
raw_Z = SetMatrix(raw_X, {"6"});
//raw_Y = RowMatrix(raw_X, -35);
//ShuffleMatrixRows(raw_Y);

auto [X_train, X_test, Y_train, Y_test] = train_test_split(raw_Y,raw_Z, 1);
std::cout<< Y_test <<std::endl;




return 1;
}