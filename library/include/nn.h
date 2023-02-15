/**
 * @file nn.h
 * @brief lightweight neural network engine of phoenixs library .
 */

#ifndef NN_H
#define NN_H

#include "Vector.h"

using namespace phoenix;

struct data
{
    Matrix<double> input;    /*2D array of input features*/
    Matrix<double> label;  /*2D array of output labels*/

    /* data */
};




class NeuralModel {

private:
    Vector<double> w;  //pointer to array that has the weight
    Vector<double> x;   //weight from the hidden layer to output layer
    Vector<double> b;   //biases
    Vector<double> h;   //hidden layer
    Vector<double> o;   //output layer  

    int no_b;    //number of biases
    int no_w;    //number of weight
    int no_i;    //number of input
    int no_n;     //number of hidden neuron
    int no_o;  //number of output
    


public:
    /**
     * @brief Constructs a neural network model object.
     */
    NeuralModel ();


    /**
     * @brief Destructs a neural network model.
     */
    ~NeuralModel ();;

    Vector<double> predict(Vector<double> input);
    data build();
    Vector<double> train(Vector<double> in, Vector<double> tg, double rate);
    void save(const char * path);
    NeuralModel load(const char * path);
    void print();





    


};




#endif