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

public:
    Matrix<double> feature;
    Matrix<double> label;
    Tensor<T> network;
    std::initializer_list<int> hids;
    std::vector<Vector<T>> B;
    std::vector<Vector<T>> target;
    int no_hid = 0;
    double learning_rate = 0.01;


    //double act(double value) {return sigmoid_derivative(value);}

public:
    /**
     * @brief Constructs a neural network model object.
     */
    NeuralModel (Matrix<double> &in,
                 Matrix<double> &out,
                 std::initializer_list<int> hidden_neurons,
                 double rate) : feature(in), label(out), hids(hidden_neurons), learning_rate(rate) 
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

        target.push_back(output);

        int bk_n = input.size();
        

        network.addMatrix(input);
        

        for (auto n: hids)     
        {
            Vector<T> neurons(n);
            Vector<T> hidden_bias(n);

            Matrix<T> weight(n,bk_n);

            weight.randfill();
            hidden_bias.randfill();

            network.addMatrix(weight);
            network.addMatrix(neurons);
            B.push_back(hidden_bias);


            bk_n = neurons.size();
        }

        int last_n = output.size();

        Vector<T> output_bias(last_n);
        B.push_back(output_bias);
        

        Matrix<T> weight(last_n, bk_n);
        weight.randfill();
        network.addMatrix(weight);
        network.addMatrix(output);
        

       // network.print();
    }

    void forward_propagation(){

        int layer= 0;
        int i = 0;

        //Calculate output of hidden layer
        for ( i = 0; i < no_hid; i++)
        {
           auto hidden_layer = convert_col(network[layer++], 0);
        

          // auto p = vecTomat_multiply(hidden_layer, network[layer++]);
        auto p = (network[layer++] * hidden_layer) + B[i];
        network[layer] = vector_sigmoid(p);
     
        }

        //Calculate final output  no sigmoid
        auto hidden_layer = convert_col(network[layer++], 0);
        auto p = (network[layer++] * hidden_layer);   // + B[i];
        network[layer] = p;

        network.print();
    }


    void back_propagation(){

    std::vector<Vector<double>> error;
    int count = network.size() - 1;
 
    //Extract Value of output from tensor network
    Vector<double> output =  convert_col(network[count], 0);
    Vector<double> expected_output = target[0];
    
     //calculate error for the output layer
     Vector<double> output_error(output.size());
     for (int i = 0; i < output.size(); i++)
     {
        double derr = expected_output[i] - output[i];
        output_error[i] = derr * sigmoid_derivative(output[i]);
     }
    error.push_back(output_error);
   std::cout<<"-----------------------------"<<std::endl;

    //calculate error for the hidden layer
    for (int hid = 0; hid < no_hid; hid++)
    {
        
        Matrix<double> h_weight = network[--count].transpose();
        Vector<double> hidden_n =  convert_col(network[--count], 0);
        Vector<double> h_error(hidden_n.size());


        h_error = h_weight * error[hid];

        for (int i =0; i < h_error.size(); i++)
            h_error[i] = h_error[i] * sigmoid_derivative(hidden_n[i]);

    error.push_back(h_error);

    //  std::cout<<h_weight<<std::endl;
    //  std::cout<<hidden_n<<std::endl;
    //  std::cout<< error[hid]<<std::endl;
    //   std::cout<<"-----------------------------"<<std::endl;

    }


    count = network.size() - 1;
    int iter = no_hid+1;

    //Update weights for layers 
    for (int layer = 0; layer < iter; layer++)
    {
      Matrix<double>& h_weight = network[--count];
      Vector<double> hidden_n =  convert_col(network[--count], 0);

      for (int i = 0; i < h_weight.rows; i++)
      {
        for (int j = 0; j < h_weight.cols; j++){
            double delta_weight = learning_rate * error[layer][i] * hidden_n[j];
            h_weight[i][j] += delta_weight;
        }

        //Update Bias
        B[no_hid - layer][i] += learning_rate * error[layer][i];

      }
    
    }
    network.print();
    //std::cout<<B.size()<<std::endl;
            

    }   
    

};




#endif