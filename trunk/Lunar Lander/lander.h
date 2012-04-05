#include <iostream>


using namespace std;

float ACCELERATION = 2.0; // but could be randomized
float WIND = 1; // but randomized below
const float MAX_SAFE_LANDING_SPEED = 4.0;
const float MIN_SAFE_X = -0.2;
const float MAX_SAFE_X = 0.2;

class lander {
public:
    lander(void);
    int landed_test(void) {return landed;}
    void update(network test_network);
    void print(void);
    void draw(void);
    void test(void);
    void landedDraw(void);
    void control(network test_network);
private:
    float height;
    float xPosition;
    float Yvelocity;
    float Xvelocity;
    int landed; // 0- no, 1- yes, 2- crashed
    float fuel;
    float burn;
    float thrust;
};

void lander::control(network test_network) {
    // calculates the burn - vertical adjustments
    // and the thrust - horizontal adjustments
    // both use fuel
    
    // NODES = 6 inputs: height, xPosition, Yvelocity, Xvelocity, wind, and fuel.
    float input_sensors[6] = {height, xPosition, Yvelocity, Xvelocity, WIND, fuel};
    float burn_thrust[2];

    test_network.calculate_output(input_sensors, burn_thrust);
    burn = burn_thrust[0];
    thrust = burn_thrust[1];

}

void lander::test(void) {
    // Test for landing 
    if (height > 0) // haven't landed yet
        return; //landed still = 0
    if (Yvelocity > MAX_SAFE_LANDING_SPEED || xPosition < MIN_SAFE_X || xPosition > MAX_SAFE_X)
        landed = 2;
    else
        landed = 1;
}

lander::lander(void) {
    height = 100.0; // starting height
    Yvelocity = 10.0 * lrand(); // random starting velocity
    landed = 0; // haven't landed yet
    fuel = 100.0; // starting fuel
    ACCELERATION = 2.0; // could use different acceleration for diff. planets.
    xPosition = 0;
    Xvelocity = 0;
    WIND = 0.2 * (lrand() - 0.5); // random wind 
}

void lander::update(network test_network) {
    // update the lander's altitude 
    Yvelocity += ACCELERATION; // apply acceleration
    control(test_network); // calculate burn and thrust
    if (fuel < burn) // if insuficient fuel, use the rest for burn
        burn = fuel;
    fuel -= fabs(burn); // subtract fuel
    Yvelocity -= burn; // apply burn 
    if (fuel < thrust) // if insuficient fuel, use the rest for thrust
        thrust = fuel;
    fuel -= fabs(thrust); // subtract fuel
    Xvelocity -= thrust; // apply thrust

    height -= (Yvelocity); //  subtract because moving down
    xPosition += (Xvelocity + WIND); //  wind 
}

void lander::print(void) {
    //  For command line version
    cout << "Height: " << height << "  ";
    cout << "Y-Velocity: " << Yvelocity << "  ";
    cout << "X-Position: " << xPosition << "  ";
    cout << "X-Velocity: " << Xvelocity << "   ";
    cout << "Fuel: " << fuel << endl;

}
