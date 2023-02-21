/**
 * @file nn.h
 * @brief lightweight neural network engine of phoenixs library .
 */

#ifndef NN_H
#define NN_H

#include "Matrix.h"
#include "Vector.h"
#include "utils.h"
#include <functional>


using namespace phoenix;



  template <typename T>
class NeuralModel {

private:
    Matrix<double> feature;
    Matrix<double> label;
    Tensor<T> network;
    std::initializer_list<int> hids;    //number of hidden neuron in each layer
    std::vector<Vector<T>> B;           //Biases
    std::vector<Vector<T>> target;
    int no_hid = 0;
    double learning_rate = 0.01;
    
   struct act{
    std::function<double(double)> activation;
    std::function<double(double)> derivative;
   }; 

   std::vector<act> A;    //activation_functions;

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
                    NNBuild();
                 };

    /**
     * @brief Destructs a neural network model.
     */
    ~NeuralModel()  {};

    void NNConnfigure(std::initializer_list<std::string> act_function)
    {
      //Empty all elements of activation initializer
      if (!A.empty()){
        A.clear();
      }


      for (auto fn : act_function)
      {
        act activationType;

        if (fn == "sigmoid")
        {
          activationType.activation = sigmoid;
          activationType.derivative = sigmoid_derivative;
        }
        else if (fn == "relu") 
        {
          activationType.activation = relu;
          activationType.derivative = relu_derivative;
        }
        else if (fn == "linear")
        {
          activationType.activation = linear;
          activationType.derivative = linear_derivative;
        }
        else{
          std::cout << "invalid actvation function"<<std::endl;
        }

     A.push_back(activationType); 

      }
    }

private:

    //Build NN network with input -- hidden layers and  -- output
    void NNBuild()
    {

        int bk_n = feature.getCols();
        Vector<T> input(bk_n);
        
        network.addMatrix(input);
        

        for (auto n: hids)   //Add hidden layer neurons to network    
        {
            Vector<T> neurons(n);
            Vector<T> hidden_bias(n);

            Matrix<T> weight(n,bk_n);   //construct weight matrices

            weight.randfill();
            hidden_bias.zerofill();

            network.addMatrix(weight);
            network.addMatrix(neurons);
            B.push_back(hidden_bias);

            bk_n = neurons.size();
        }

        int last_n = label.getCols();

        Vector<T> output(last_n); 
        Vector<T> output_bias(last_n);   //this is made redundant since bias is not added to output
        output_bias.zerofill();
        B.push_back(output_bias);
        

        Matrix<T> weight(last_n, bk_n);
        weight.randfill();
        network.addMatrix(weight);
        network.addMatrix(output);

       // network.print();
       act default_fn = {sigmoid, sigmoid_derivative};
       act output_fn = {linear, linear_derivative};

       for (int i = 0; i < no_hid; i++)
       {
        A.push_back(default_fn);
       }
       A.push_back(output_fn);

    }

    void forward_propagation(const Vector<T> &input){

        int layer= 0;
        int i = 0;
        network[layer] = input;

        //Calculate output of hidden layer
        for ( i = 0; i < no_hid; i++)
        {
           auto hidden_layer = convert_col(network[layer++], 0);  //convert input matrix to vector
        

          // auto p = vecTomat_multiply(hidden_layer, network[layer++]);
        auto p = (network[layer++] * hidden_layer) + B[i];
        //network[layer] = vector_sigmoid(p);
        network[layer] = vector_act(p, A[i].activation);
     
        }

        //Calculate final output  no sigmoid
        auto hidden_layer = convert_col(network[layer++], 0);
        auto p = (network[layer++] * hidden_layer);   // + B[i];
        //network[layer] = p;
        network[layer] = vector_act(p, A[no_hid].activation);

      //   network.print();

    }

    void back_propagation(const Vector<T> &expected_output){

    std::vector<Vector<double>> error;
    int count = network.size() - 1;
 
    //Extract Value of output from tensor network
    Vector<double> output =  convert_col(network[count], 0);
    // Vector<double> expected_output = target[0];
    
     //calculate error for the output layer
     Vector<double> output_error(output.size());
     for (int i = 0; i < output.size(); i++)
     {
        double derr = expected_output[i] - output[i];
        output_error[i] = derr * A[no_hid].derivative(output[i]);
     }
    error.push_back(output_error);
 


    //calculate error for the hidden layer
    for (int hid = 0; hid < no_hid; hid++)
    {
        
        Matrix<double> h_weight = network[--count].transpose();
        Vector<double> hidden_n =  convert_col(network[--count], 0);
        Vector<double> h_error(hidden_n.size());


        h_error = h_weight * error[hid];

        for (int i =0; i < h_error.size(); i++)
            h_error[i] =   h_error[i] * A[hid].derivative(hidden_n[i]);

    error.push_back(h_error);

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
     //network.print();

    }   
  
  public:

  Vector<T> NNpredict(const Vector<T> &predict)
  {
    int count = network.size() - 1;

    forward_propagation(predict);

    Vector<double> output =  convert_col(network[count], 0);

    return (output);

  }

  Vector<T> NNPredicted()
  {
    int count = network.size() - 1;

    Vector<double> output =  convert_col(network[count], 0);

    return (output);
  }

void NNTrain(int epochs = 100)
{
  double error;

  for (int count = 0; count < epochs; count++)
  {
    error = 0;
    for(int i = 0; i < feature.rows; i++)
    {
      auto input = convert_row(feature, i);
      auto target = convert_row(label, i);

      forward_propagation(input);
      back_propagation(target);

      error += total_error(target,  NNPredicted());
    }

    std::cout<<"Epoch----- "<< count << " Error: "<<error/feature.rows<<std::endl;
  }

}
    

};




#endif