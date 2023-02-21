#include <iostream>
#include <cmath>




double sigmoid(double x){
        double result;
        result = 1/(1 + std::exp(-x));

        return result;
    }

 
double sigmoid_derivative(double a){
        double result;
        result = sigmoid(a) * (1.0 - sigmoid(a));

        return result;
    }  

double relu(double x){
        
        return std::max(0.0, x);
    }

 
double relu_derivative(double a){

        return ( a > 0.0) ? 1.0 : 0.0;
    }  


double linear(double x){
        
        return x;
    }

 
double linear_derivative(double a){

        return 1;
    }  


