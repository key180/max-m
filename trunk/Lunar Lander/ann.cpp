/* 
 * File:   ann.cpp
 * Author: mcki4229
 * 
 * Created on April 2, 2012, 10:05 AM
 */

#include <math.h>
#include <iostream>
#include "ann.h"
using namespace std;

void neuron::test(){
    
}
void neuron::randomize_all_weights(){
    for(int i = 0; i < NODES; i++){
        weights[i] = rand()/float(RAND_MAX)*10 - 5; //Scaled from -5 to 5

    }
    bias_weight = rand()/float(RAND_MAX)*10 - 5;
}

float neuron::sigmoid(float input){
    return 1/(1+exp(-input)); // Later replace with a lookup table for -inf to inf, returns a value 0 to 1
}

float neuron::sum_of_weighted_inputs(float inputs[]){
    //Returns a sum, in_j, of input weights (a_i * w_ij)
    float sum = 0;
    for(int i = 0; i < NODES; i++){
        sum += weights[i]*inputs[i];
    }
    sum += bias_weight;
    return sum;
}

void layer::get_outputs(float in[], float out[]){
    //Calculate outputs a_j for current node column, return outputs by reference to inputted array
    float weighted_sum; // in_j
    for(int i = 0; i < NODES; i++){
        weighted_sum = column_of_nodes[i].sum_of_weighted_inputs(in);
        out[i] = column_of_nodes[i].sigmoid(weighted_sum);
    }
}

void network::calculate_output(float in[], float final_out[]){
    // NODES = 6 inputs: height, xPosition, Yvelocity, Xvelocity, wind, and fuel.
    // Outputs burn and thrust - updates final_out array
    
    float out[NODES];
    float temp[NODES];
    float weighted_sum;
    
    //copy in to temp
    for(int i = 0; i < NODES; i++){
        temp[i] = in[i];
    }
    for(int j = 0; j < 2; j++){ //2 is for number of outputs
        hidden_layer[j].get_outputs(temp, out); //updates out by reference
        //copy output to temp
        for (int i = 0; i < NODES; i++) {
            temp[i] = out[i];
        }
    }
    
    //inputs to final layer
    for (int i = 0; i < 2; i++) {
        weighted_sum = outputs[i].sum_of_weighted_inputs(out);
        final_out[i] = outputs[i].sigmoid(weighted_sum);
    }
    
    final_out[0] *= 20; // Burn range from 0 - 20: Expert knowledge,
    final_out[1] = final_out[1]*5 - 2.5; // Thrust range from -2.5 to 2.5: Expert knowledge
   
}

void network::randomize_network_weights(){
    //Randomize all of the node weights in the network
    for(int i = 0; i < 2; i ++){ // step through hidden layers
        for(int j = 0; j < NODES; j++){
            hidden_layer[i].column_of_nodes[j].randomize_all_weights();
        }
    }
    outputs[0].randomize_all_weights();
    outputs[1].randomize_all_weights();
}

void network::print_network_weights() {
    //Output the network in an easier to see format (with the weights)
    for (int i = 0; i < 2; i++) { // step through hidden layers
        for (int j = 0; j < NODES; j++) {
            cout << "Layer: " << i << " Node: " << j << endl;
            cout << "[ ";
            for (int k = 0; k < NODES; k++){
                cout << hidden_layer[i].column_of_nodes[j].weights[k]
                        << ", ";
            }
            cout << "bias: " << hidden_layer[i].column_of_nodes[j].bias_weight
                    << " ]\n" << endl;
            
        }
    }
    
    cout << "Output Weights" << endl;
    for (int i = 0; i < 2; i++) {
        for (int k = 0; k < NODES; k++) {
            cout << outputs[i].weights[k]
                    << ", ";
        }
        cout << "bias: " << outputs[i].bias_weight
                << " ]\n" << endl;
    }
}
    
