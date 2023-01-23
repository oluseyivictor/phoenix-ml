/**
 * @file nn.h
 * @brief lightweight neural network engine of gherkins library .
 */

#ifndef NN_H
#define NN_H

#include "Vector.h"

using namespace gherkin;

double weighted_sum(const Vector & input, const Vector & weight);

class Model {


public:
    /**
     * @brief Constructs a neural network model object.
     */
    Model() {};


    /**
     * @brief Destructs a neural network model.
     */
    ~Model() {};


    /**
     * @brief Single input single output neural network.
     *
     * @param input The value of the input element.
     * @param weight The weight attached with the input.
     *
     * @return A predicted value which is input multiplied by weight.
     */
    double single_nn(double input, double weight) { return(input*weight); }


    


};




#endif