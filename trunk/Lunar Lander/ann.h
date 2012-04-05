/* 
 * File:   ann.h
 * Author: mcki4229
 *
 * Artificial Neural Network
 * 
 * 2 outputs: burn, thrust
 * 
 * Set weights by hand to start, but then train and analyze 
 * 
 * Created on April 2, 2012, 10:05 AM
 * 
 * 4/2 Node object outline
 */
const int NODES = 6;

#ifndef ANN_H
#define	ANN_H


class neuron {
public:
    float weights[NODES]; // array of weights
    float bias_weight; // bias weight for node
    
    float sigmoid(float input); // returns output a_j of node
    float sum_of_weighted_inputs(float inputs[]);
    void randomize_all_weights();
    void test();
};

class layer {
public:
    neuron column_of_nodes[NODES];
    
    void get_outputs(float in[], float out[]); //gets outputs and updates by reference
    
};

class network {
public:
     
    neuron outputs[2]; // 2 outputs: burn and thrust
    layer hidden_layer[2];
    float fitness;
    
    void calculate_output(float in[], float out[]);
    void randomize_network_weights();
    void print_network_weights();
    void set_weights(float in[2][NODES][NODES+1], float final_ins[2][NODES+1]);
};

#endif	/* ANN_H */

