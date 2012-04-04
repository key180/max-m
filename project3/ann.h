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

class ann {
public:
    ann();
    ann(const ann& orig);
    virtual ~ann();

};

class neuron {
public:
    float weights[NODES]; // array of weights
    float bias_weight; // bias weight for node
    
    float sigmoid(float input); // returns output a_j of node
    void randomize_all_weights();
};

class layer {
public:
    neuron hiddenlayer[NODES];
    
};

class network {
public:
    float inputs[NODES]; // NODES = 6 inputs: height, xPosition, Yvelocity, Xvelocity, wind, and fuel. 
    float outputs[2]; // 2 outputs: burn and thrust
    
};

#endif	/* ANN_H */

