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

        int num_inputs;
        int num_hidden;
        int num_outputs;
        double learning_rate;
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
        //    if ( error > 100) error = 100;
        //    else error = 100 - error;

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
        
        int bias_size = NeuralModel::B.size();
        for (int i = 0; i < bias_size; i++ )
        {
            Matrix<double> bias = NeuralModel::B[i];
            std::cout<<bias<<std::endl;
            file.write(reinterpret_cast<char*>(bias.getdata()), bias.size() * sizeof(double)) ;       

        }

        int network_size = NeuralModel::network.size() - 1;
        for (int i = 1; i < network_size; i = i+2 )
        {
            Matrix<double> weight = NeuralModel::network[i];
            std::cout<<weight<<std::endl;
            file.write(reinterpret_cast<char*>(weight.getdata()), weight.size() * sizeof(double)) ;       

        }

        file.close();
    }

};


#endif