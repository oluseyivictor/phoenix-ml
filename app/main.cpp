#include <iostream>
#include "Matrix.h"
#include "Vector.h"
#include "config.hpp"

using namespace gherkin;

int main(){

    std::cout<< project_name <<std::endl;
    std::cout<< project_version <<std::endl;

double ment2[3] = {0.2,0.4,0.6};

     Vector myvalue(3);
     myvalue<<ment2;
     Vector Newv(3);
     myvalue *= 2;
    myvalue.print();


    return 1;
}