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

int main() {

    srand(time(NULL));
    lander l;
    network test_network;
    
    test_network.randomize_network_weights();
    test_network.print_network_weights();
    
    //neural network code
    
    
    
    //main loop
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

    return 0;
}

float lrand(void) {
    return (rand() / float(RAND_MAX));
}
