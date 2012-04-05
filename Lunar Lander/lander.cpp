/**************************
 * Includes
 *
 **************************/

#include<ctime>
#include<cmath>
#include<iostream>
using namespace std;



/**************************
 * Function Declarations
 *
 **************************/

float lrand(void); // random 0-1

#include "ann.h"
#include "lander.h"


class individual{
public:
    //individual is a container class for weights
    float in[2][NODES][NODES + 1]; // 3D array [column][node in column][weight in column]
    float final_ins[2][NODES + 1];
    float fitness;
    
    individual();
    
};

individual::individual(){
    //initialize w random values
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < NODES; j++) {
            for (int k = 0; k < NODES + 1; k++) {
                in[i][j][k] = rand() / float(RAND_MAX)*10 - 5; //Scaled from -5 to 5;
            }
        }
    }
    for (int j = 0; j < 2; j++) {
        for (int k = 0; k < NODES + 1; k++) {
            final_ins[j][k] = rand() / float(RAND_MAX)*10 - 5; //Scaled from -5 to 5
        }
    }
    
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

int main() {
    const int GEN = 100; // # of generations
    srand(time(NULL));
    lander l;
    network test_network;
    
    float fitnesspergen[GEN];
    
    
    for(int gen = 0; gen < GEN; gen++){

        //neural network code
        test_network.randomize_network_weights();
        test_network.print_network_weights();

        //Setup array of zero weights to feed network - 
        float in[2][NODES][NODES + 1]; // 3D array [column][node in column][weight in column]
        float final_ins[2][NODES + 1];

        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < NODES; j++) {
                for (int k = 0; k < NODES + 1; k++) {
                    in[i][j][k] = 0;
                }
            }
        }

        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < NODES + 1; k++) {
                final_ins[j][k] = 0;
            }
        }
        test_network.set_weights(in, final_ins);
        test_network.print_network_weights();




        //main loop run the lunar lander game
        while (!l.landed_test()) {
            l.update(test_network); // update position and velocity
            l.print();
            l.test(); // test for landing/crash
        }

        if (l.landed_test() == 1) {
            cout << "$$$$SAFE$$$$" << endl;
        }
        if (l.landed_test() == 2) {
            cout << "$$$$CRASH$$$$" << endl;
        }
        fitnesspergen[gen] = l.get_fitness();

        l = *(new lander());
    }
    for (int gen = 0; gen < GEN; gen++) {
        cout << "Fitness: " << fitnesspergen[gen];
    }
    
    return 0;
}

float lrand(void) {
    return (rand() / float(RAND_MAX));
}
