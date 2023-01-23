#include "Vector.h"



namespace gherkin {



double* create_array(int row, const Vector t){
double* Point = new double[row];
for (int i = 0; i < t.row(); i++) {
    Point[i] = t[i];
}
  return Point;
}

Vector& Vector::operator*= (double scalar) {
    for (int i = 0; i < row(); i++) {
        data[i][0] *= scalar;
    }
    return *this;
}



void Vector::multiply(double scalar,  Vector &t ){
     for (int i = 0; i < row(); i++) {
        data[i][0] = t.data[i][0] * scalar;
    }
}
    
double& Vector::operator[](int i) {
    return Matrix::operator()(i, 0);
}

const double& Vector::operator[](int i) const {
    return Matrix::operator()(i, 0);
}


}