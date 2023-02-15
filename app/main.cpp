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

//Matrix<double> raw_Y(3);    //Matrix<double> raw_Y(3);  raw_Y = {200, 90, 100};
//raw_Y = {{200, 90, 100}};

//auto train_X = raw_X.scale();
//auto train_Y = raw_Y.scale();

//std::cout<< raw_X  <<std::endl;

//ShuffleMatrixRows(raw_X);

auto Tr = convert_col(raw_X, 7);

std::cout<< Tr <<std::endl;



return 1;
}