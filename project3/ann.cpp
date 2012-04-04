/* 
 * File:   ann.cpp
 * Author: mcki4229
 * 
 * Created on April 2, 2012, 10:05 AM
 */

#include "ann.h"
#include <stdlib.h>


ann::ann() {
}

ann::ann(const ann& orig) {
}

ann::~ann() {
}

void neuron::randomize_all_weights(){
    for(int i = 0; i < NODES; i++){
        weights[i] = rand()/float(RAND_MAX)*5 - 10; //Scaled from -5 to 5
        std::cout << weights[i] << " weights";

    }
    bias_weight = rand()/float(RAND_MAX)*5 - 10;
    
}

float neuron::sigmoid(float input){
    return 1/(1+exp(-input)); // Later replace with a lookup table for -inf to inf, returns a value 0 to 1
}