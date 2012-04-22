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

#include "fuzzy.h"
#include "lander.h"
#include <fstream>


class individual{
public:
    //individual is a container class for weights for whole neural network
    float fitness;
    
    individual();
    
};

individual::individual(){

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

float test_weights_fitness(int print_on) {
    //test an individual (set of network weights) and update the individual's fitness
    lander l;

    float average;
    float running_sum = 0;
    float current_fitness;
    const int NUM_TRIALS = 1;
    
    for (int q = 0; q < NUM_TRIALS; q++) {
        l.init();

        //main loop run the lunar lander game
        while (!l.landed_test()) {
            l.update(); // update position and velocity
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

    return average; // return average fitness
}

void mutate_individual(individual& input) {
    //Randomly mutate a weight of an individual
}

float lrand(void) {
    
    return (rand() / float(RAND_MAX));
}
