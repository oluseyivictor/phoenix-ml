/**
 * @file matrix.h
 * @brief This file contains the declaration of the Matrix class.
 */

#ifndef SIMPLE_NN_H
#define SIMPLE_NN_H

#include "nn.h"
#include "nn_interface.h"
#include <fstream>

using namespace phoenix;


class SimpleNeuralNetwork : public NeuralModel, public INeuralNetwork {
    public:

        Matrix<double> input;
        Matrix<double> output;
        std::vector<int> H;    //number of hidden neuron in each layer

        int num_inputs;
        int num_hidden;
        int num_outputs;
        double learning_rate;
        int value;
        //create a new struct from predicted for load and save --- to be added
    
    public:
    SimpleNeuralNetwork (Matrix<double> &rin,
                 Matrix<double> &rout,
                 std::initializer_list<int> rhidden_neurons,
                 double rrate): NeuralModel(rin, rout, rhidden_neurons, rrate), input(rin) , output(rout)
                 {


                    num_inputs = rin.getCols();
                    num_hidden = rhidden_neurons.size();
                    num_outputs = rout.getCols();
                    learning_rate = rrate;

                    for (int n: rhidden_neurons){
                        H.push_back(n);
                    }

                 }
         SimpleNeuralNetwork(): NeuralModel()
         {

         }

     void train(const int epochs = 100){
         double error;

         for (int count = 0; count < epochs; count++)
         {
           error = 0;
           for(int i = 0; i < input.getRows(); i++)
            {
              auto in = convert_row(input, i);
              auto target = convert_row(output, i);

              NeuralModel::forward_propagation(in);
              NeuralModel::back_propagation(target);

            error += total_error(target,  NeuralModel::NNPredicted());
          }
          error = error/input.getRows();
           std::cout<<"Epoch----- "<< count << " Error: "<<error<<std::endl;
         }
 }

    Vector<double> predict(const Vector<double> &predict){
        int count = NeuralModel::network.size() - 1;

        NeuralModel::forward_propagation(predict);

        Vector<double> output =  convert_col(NeuralModel::network[count], 0);

    return (output);

  }

   void configure(std::initializer_list<std::string>& act_value)
   {
        NeuralModel::NNConnfigure(act_value);
   }



  void save(std::string filename) {

        std::ofstream file(filename, std::ios::out | std::ios::binary);
        if (!file) {
            std::cerr << "Error: Could not open file " << filename << " for writing\n";
            return;
        }
        
        file.write(reinterpret_cast<char*>(&num_inputs), sizeof(num_inputs));
        file.write(reinterpret_cast<char*>(&num_hidden), sizeof(num_hidden));
        file.write(reinterpret_cast<char*>(&num_outputs), sizeof(num_outputs));
        file.write(reinterpret_cast<char*>(&learning_rate), sizeof(learning_rate));

        
        for (auto vals: H){
            file.write(reinterpret_cast<char*>(&vals), sizeof(vals));
        }
        
        int network_size = NeuralModel::network.size() - 1;
        for (int i = 1; i < network_size; i = i+2 )
        {
            Matrix<double> weight = NeuralModel::network[i];
            file.write(reinterpret_cast<char*>(weight.getdata()), weight.size() * sizeof(double)) ;       

        }

                
        
        int bias_size = NeuralModel::B.size();
        for (int i = 0; i < bias_size; i++ )
        {
            Vector<double> bias = NeuralModel::B[i];
            file.write(reinterpret_cast<char*>(bias.getdata()), bias.size() * sizeof(double)) ;       

        }
        file.close();
    }

    void load(std::string filename) {
        std::ifstream file(filename, std::ios::in | std::ios::binary);
        if (!file) {
            std::cerr << "Error: Could not open file " << filename << " for reading\n";
            return;
        }
        file.read(reinterpret_cast<char*>(&num_inputs), sizeof(num_inputs));
        file.read(reinterpret_cast<char*>(&num_hidden), sizeof(num_hidden));
        file.read(reinterpret_cast<char*>(&num_outputs), sizeof(num_outputs));
        file.read(reinterpret_cast<char*>(&learning_rate), sizeof(learning_rate));


        std::vector<int> nl;

        for (int i = 0; i < num_hidden; i++ )
        {
            file.read(reinterpret_cast<char*>(&value), sizeof(value));
            nl.push_back(value);   

        }

        NNBuild(num_inputs, num_outputs, nl);

        int network_size = NeuralModel::network.size() - 1;
        for (int i = 1; i < network_size; i = i+2 )
        {
            Matrix<double> &weight =  NeuralModel::network[i];
           file.read(reinterpret_cast<char*>(weight.getdata()), weight.size() * sizeof(double));   

        }

        B.clear();
        for (int i = 0; i < num_hidden; i++ )
        {
            Vector<double> bias(nl[i]);
            file.read(reinterpret_cast<char*>(bias.getdata()), bias.size() * sizeof(double));  
            B.push_back(bias);

        }
        file.close();
    }
};




#endif