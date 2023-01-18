#include <iostream>
#include "Matrix.h"
#include "Vector.h"


int main(){

    double ment[12] = {0.2,0.4,0.6,0.1,0.2,0.9,0.3,0.0,0.6,2.1,3.5,1.4};
     Matrix myvals(3, 4);
     myvals<<ment;
     myvals.print();
     std::cout<<myvals.size()<<std::endl;

double ment2[3] = {0.2,0.4,0.6};

     Vector myvalue(3);
     myvalue<<ment2;
     Vector Newv(3);
     myvalue *= 2;
    myvalue.print();


    return 1;
}