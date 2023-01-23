#include <iostream>
#include "config.hpp"
#include "nn.h"
#include "Vector.h"
#include <nlohmann/json.hpp>



using namespace gherkin;

int main(){

Model pred;
Vector newVector = 5;
Vector oldVector(5);

double newData[5] = {1,2,3,4,5};
double nData[5] = {1,2,3,4};

oldVector<<newData;
newVector.multiply(5, oldVector);

newVector.print();

std::cout<< weighted_sum(newVector, oldVector)<<std::endl;




    return 1;
}