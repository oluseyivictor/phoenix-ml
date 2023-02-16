/**
 * @file nn.h
 * @brief lightweight neural network engine of phoenixs library .
 */

#ifndef NN_H
#define NN_H

#include "Matrix.h"
#include "Vector.h"
#include "utils.h"

using namespace phoenix;



  template <typename T>
class NeuralModel {

private:
    Matrix<double> input;
    Matrix<double> output;
    Tensor<T> network;
    std::initializer_list<int> hids;
    std::vector<double> biases;
    int no_hid = 0;

public:
    /**
     * @brief Constructs a neural network model object.
     */
    NeuralModel (Matrix<double> &in,
                 Matrix<double> &out,
                 std::initializer_list<int> hidden_neurons) : input(in), output(out), hids(hidden_neurons) 
                 {
                    no_hid = hidden_neurons.size();
                 };

    /**
     * @brief Destructs a neural network model.
     */
    ~NeuralModel()  {};

    //template <typename T>
    void construct_network(const Vector<T> &input,
                           const Vector<T> &output)
    {

        network.addMatrix(input);

        for (auto n: hids)
        {
            Vector<T> neurons(n);
            Matrix<T> weight(3,3);

            weight.randfill();

            network.addMatrix(weight);
            network.addMatrix(neurons);
        }

        Matrix<T> weight(3,3);
        weight.randfill();
        network.addMatrix(weight);
        network.addMatrix(output);

       // network.print();
    }

    void forward_propagation(){

        int layer= 0;

        for (int i = 0; i < no_hid+1; i++)
        {
           auto hidden_layer = convert_col(network[layer++], 0);
        //   std::cout<<hidden_layer<<std::endl;
           Matrix<T> weight = network[layer++];
         //  std::cout<<weight<<std::endl;
           auto p = vecTomat_multiply(hidden_layer, weight );
         //   std::cout<<p<<std::endl;
        
          Matrix<T> newr = network[layer];
        //  std::cout<<"---"<<newr<<std::endl;
          
          for (int k = 0; k < newr.size(); k++)
          newr[k][0] = sigmoid(p[k]);
        }

        network.print();
    }


    // template <typename T>
    // void forward_propagation(){
    //     int input = 0;

};




#endif