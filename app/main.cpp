#include <iostream>
#include "config.hpp"
#include "io.h"
#include "utils.h"
#include "nn.h"
#include "Matrix.h"
#include "Vector.h"
#include <nlohmann/json.hpp>

using namespace phoenix;

int main() {


Matrix<double>raw_X(4,3);
Matrix<double>raw_Y(4,2);

 //ReadFileToMatrix("../../app/data.txt", raw_X);
// raw_X =Matrix<double>(3,34);

raw_X = {{2, 8, 5}, {2, 8, 5}, {2, 8, 5}, {2, 8, 5}};
raw_Y = {{1,4}, {1,4},{1,4},{1,4}};                                                 

// Vector<double> raw_Y(256);    //Matrix<double> raw_Y(3);  raw_Y = {200, 90, 100};
// Vector<double> raw_Z(10); 
// raw_Z = {201, 90, 100, 74};
// raw_Y = {0.12, 0.90, 0.545, 0.8};
// //auto raw_P = convert_col(raw_X, 0);
// auto train_X = raw_X.scale();
// auto train_Y = raw_Y.scale();

// std::cout<< raw_X  <<std::endl;
// std::cout<< raw_X.getCols()  <<std::endl;

// std::cout<< raw_L  <<std::endl;
// std::cout<< raw_L.getCols()  <<std::endl;

//ShuffleMatrixRows(raw_X);

//auto Tr = convert_col(raw_X, 7);


// raw_Y = SetMatrix(raw_X, {"0","1","2","3","4"});
// raw_Z = SetMatrix(raw_X, {"6"});
// //raw_Y = RowMatrix(raw_X, -35);
// //ShuffleMatrixRows(raw_Y);

// auto [X_train, X_test, Y_train, Y_test] = train_test_split(raw_Y,raw_Z, 1);
// std::cout<< Y_test <<std::endl;

 NeuralModel<double> nn(raw_X, raw_Y, {10}, 0.001);


//nn.NNConnfigure({"linear","linear"});


nn.NNTrain(5);

auto input = convert_row(raw_X, 1);

std::cout<< nn.NNpredict(input) <<std::endl;





//  nn.forward_propagation();










return 1;
}