/**************************
 * Includes
 *
 **************************/

#include<ctime>
#include<cmath>
#include<iostream>
#include<cstdlib>
using namespace std;



/**************************
 * Function Declarations
 *
 **************************/

float lrand(void); // random 0-1

#include "ann.h"
#include "lander.h"
#include <fstream>


class individual{
public:
    //individual is a container class for weights for whole neural network
    float in[2][NODES][NODES + 1]; // 3D array [column][node in column][weight in column]
    float final_ins[2][NODES + 1];
    float fitness;
    
    individual();
    
};

individual::individual(){
    //initialize individual
    
    //initialize zeros
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < NODES; j++) {
            for (int k = 0; k < NODES + 1; k++) {
                in[i][j][k] = 0; //Scaled from -5 to 5;
            }
        }
    }
    for (int j = 0; j < 2; j++) {
        for (int k = 0; k < NODES + 1; k++) {
            final_ins[j][k] = 0; //Scaled from -5 to 5
        }
    }
    
//    for (int i = 0; i < 2; i++) {
//        for (int j = 0; j < NODES; j++) {
//            for (int k = 0; k < NODES + 1; k++) {
//                in[i][j][k] = rand() / float(RAND_MAX)*10 - 5; //Scaled from -5 to 5;
//            }
//        }
//    }
//    for (int j = 0; j < 2; j++) {
//        for (int k = 0; k < NODES + 1; k++) {
//            final_ins[j][k] = rand() / float(RAND_MAX)*10 - 5; //Scaled from -5 to 5
//        }
//    }
    
        //Setting a few weights by hand -- expert knowledge
    in[0][0][0] = -1.0/100.0; // height * 1/100
    in[0][0][2] = 1.0/2.0; // Yvel * 1/2
    in[0][0][6] = 2; // bias weight
    in[1][0][0] = 1; // feed forward
    
    in[0][1][3] = 1; // Xvel * .7
    in[0][1][4] = 1; // wind * .7
    in[1][1][1] = 1; // feed forward
    
    final_ins[0][0] = 1; //feed forward
    final_ins[0][6] = -3; // bias weight to get burn about 2 for testing
    final_ins[1][1] = 1; // feed forward
    final_ins[1][6] = -.8; //bias thrust
}

float test_weights_fitness(individual& test_weights, int print_on);
void mutate_individual(individual& input);

int main() {
    const int GEN = 10000; // # of generations
    const int POPSIZE = 100;
    
    srand(time(NULL));
    ofstream fileout;
    
    float fitnesspergen[GEN];
    individual current;
    individual test;
    test_weights_fitness(current,0);
    
    for(int gen = 0; gen < GEN; gen++){
        
        //Be careful about deep copying / shallow copying here
        
        test = current; // !@#$!@^% Later Check that this is indeed deep copying (NOT matching pointer)
        mutate_individual(test);
        test_weights_fitness(test,0);
        if (test.fitness < current.fitness){ // If it has a better fitness, update it
            current = test; // Again check deeep copying
        }

        fitnesspergen[gen] = current.fitness;
          
    }
    test_weights_fitness(current,1);
    
    fileout.open("fit_per_gen.txt");
    for (int gen = 0; gen < GEN; gen++) {
        fileout << gen << ", " << fitnesspergen[gen] << endl;
    }
    fileout.close();
    
    //run game once with output now to see how it does.
    
    
    return 0;
}

float test_weights_fitness(individual& test_weights, int print_on) {
    //test an individual (set of network weights) and update the individual's fitness
    lander l;
    network test_network;
    float average;
    float running_sum = 0;
    float current_fitness;
    const int NUM_TRIALS = 100;
    
    for (int q = 0; q < NUM_TRIALS; q++) {
        l.init();
        test_network.set_weights(test_weights.in, test_weights.final_ins);
        //test_network.print_network_weights();

        //main loop run the lunar lander game
        while (!l.landed_test()) {
            l.update(test_network); // update position and velocity
            if (print_on == 1 && q == 0) {
                l.print();
            }
            l.test(); // test for landing/crash
        }

        if (print_on == 1) {
            if (l.landed_test() == 1) {
                cout << "1" << endl; // safe
            }
            if (l.landed_test() == 2) {
                cout << "0" << endl; // crash
            }
        }
        current_fitness = l.get_fitness();
    
        running_sum += current_fitness;
    }
    
    average = running_sum / (1.0 * NUM_TRIALS);
    test_weights.fitness = average;
    return average; // return average fitness

}

void mutate_individual(individual& input) {
    //Randomly mutate a weight of an individual
    //
    
//    float in[2][NODES][NODES + 1]; // 3D array [column][node in column][weight in column]
//    float final_ins[2][NODES + 1];
    int r1 = rand() % 2; //Random number in range 0 to 1 for hidden layer #
    int r2_output = rand() % 2; //Random number in range 0 to 1 for output
    int r2 = rand() % (NODES + 2); // Random number in range 0 to NODES + 2 - 1
    int r3 = rand() % NODES + 1; // Random number 0 to NODES + 1 - 1
    
    float new_random_weight = rand()/float(RAND_MAX)*10 - 5; // -5 to 5 floating point
    
    if (r2 == NODES || r2 == NODES +1){ // Pick output nodes to modify
        input.final_ins[r2_output][r3] = new_random_weight;
    }
    
    else{ // Pick non output nodes to modify
        input.in[r1][r2][r3] = new_random_weight;
    }
}

float lrand(void) {
    return (rand() / float(RAND_MAX));
}
