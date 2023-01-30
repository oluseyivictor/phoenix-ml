 /*
 * @file nn.cpp
 * @brief this file contains implementaion of phoenixs neural network library .
 */
#include "nn.h"


double weighted_sum(const Vector & input, const Vector & weight)
{
    double output = 0;

    for(int i=0; i<input.row(); i++){

        output += input[i]*weight[i];

    }
    return output;
}