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

float test_fitness(int print_on);
void mutate_individual(individual& input);

int main() {
    const int GEN = 1; // # of generations
    const int POPSIZE = 1;
    
    srand(time(NULL));
    ofstream fileout;
    
    float fitnesspergen[GEN];
    test_fitness(1);
    
    for(int gen = 0; gen < GEN; gen++){
        //test_fitness(0);
    }
    test_fitness(1);
    fileout.open("fit_per_gen.txt");
    for (int gen = 0; gen < GEN; gen++) {
        fileout << gen << ", " << fitnesspergen[gen] << endl;
    }
    fileout.close();
    return 0;
}

float test_fitness(int print_on) {
    //test an individual fuzzy control
    lander l;
    float average;
    float running_sum = 0;
    float current_fitness;
    const int NUM_TRIALS = 1;
    
    for (int q = 0; q < NUM_TRIALS; q++) {
        l.init();
        if (print_on == 1 && q == 0) {
            l.print();
        }
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
                cout << "1" << endl; 
                // safe
                cout << "Safe" << endl;
            }
            if (l.landed_test() == 2) {
                cout << "0" << endl; 
                // crash
                cout << "Crash" << endl;
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
    //return random floating point 0.0 to 1.
    return (rand() / float(RAND_MAX));
}