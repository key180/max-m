#include <iostream>
using namespace std;

float ACCELERATION = -2.0; // but could be randomized
float WIND = 1; // but randomized below
const float MAX_SAFE_LANDING_SPEED = -4.0;
const float MIN_SAFE_X = -0.2;
const float MAX_SAFE_X = 0.2;

class lander {
public:
    lander(void);
    void init();
    int landed_test(void) {return landed;}
    void update();
    void print(void);
    void draw(void);
    void test(void);
    void landedDraw(void);
    void control();
    float get_fitness();
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
float lander::get_fitness(){
    //expert knowledge - return fitness based on y velocity and x position
    //fitness from 0 to ...? shouldn't overflow though. Max ~~ 100
    //0 is best fitness
    //Max fitness for a safe landing is 2.0
    float tempposition = xPosition;
    if (tempposition < 0){ // make float positive
        tempposition *= -1;
    }
    return (tempposition)/MAX_SAFE_X + (Yvelocity)/MAX_SAFE_LANDING_SPEED; // 20x scaling to get to same importance level
}
void lander::control() {
    // calculates the burn - vertical adjustments
    // and the thrust - horizontal adjustments
    // both use fuel
    
    // NODES = 6 inputs: height, xPosition, Yvelocity, Xvelocity, wind, and fuel.
    float input_sensors[6] = {height, xPosition, Yvelocity, Xvelocity, WIND, fuel};
   
        
    //Start of Fuzzy Logic
    //********
    float fburn,
    fthrust; // fuzzy outcomes

    //****
    //Controller for x position
    //
    FuzzyXpos fXpos;
    fXpos.FuzzifyInput(xPosition);
    //cout << fXpos.left << " : " << fXpos.right << endl;
    
    if (fXpos.left > fXpos.right){
        fthrust = -WIND;
    }
    if (fXpos.right > fXpos.left){
        fthrust = -WIND;
    }
    
    //****
    //Controller for y velocity
    //
    FuzzyYvel fYvel;
    fYvel.FuzzifyInput(Yvelocity);
    
    fburn = fYvel.safe*1.5 + fYvel.fast*7;
    
    burn = fburn;
    thrust = fthrust;
    
//    cout << "Burn: " << burn << endl;
//    cout << "Thrust: " << thrust << endl;

}

void lander::test(void) {
    // Test for landing 
    if (height > 0) // haven't landed yet
        return; //landed still = 0
    if (Yvelocity < MAX_SAFE_LANDING_SPEED || xPosition < MIN_SAFE_X || xPosition > MAX_SAFE_X)
        landed = 2;
    else
        landed = 1;
}

lander::lander(void) {
    height = 100.0; // starting height
    Yvelocity = -10.0 * lrand(); // random starting velocity
    landed = 0; // haven't landed yet
    fuel = 100.0; // starting fuel
    ACCELERATION = -2.0; // could use different acceleration for diff. planets.
    xPosition = 0;
    Xvelocity = 0;
    //WIND = 0.2 * (lrand() - 0.5); // random wind 
}

void lander::init(){ // copy of constructor for testing purposes
    height = 100.0; // starting height
    Yvelocity = -10.0 * lrand(); // random starting velocity
    landed = 0; // haven't landed yet
    fuel = 100.0; // starting fuel
    ACCELERATION = -2.0; // could use different acceleration for diff. planets.
    xPosition = 0;
    Xvelocity = 0;
    WIND = 0.2 * (lrand() - 0.5); // random wind 
}

void lander::update() {
    // update the lander's altitude 
    control(); // calculate burn and thrust
    Yvelocity += ACCELERATION; // apply acceleration
    if (fuel < burn) // if insuficient fuel, use the rest for burn
        burn = fuel;
    fuel -= fabs(burn); // subtract fuel
    Yvelocity += burn; // apply burn 
    if (fuel < thrust) // if insuficient fuel, use the rest for thrust
        thrust = fuel;
    fuel -= fabs(thrust); // subtract fuel
    Xvelocity = thrust; // apply thrust

    height += (Yvelocity); //  subtract because moving down
    xPosition += (Xvelocity + WIND); //  wind 
}

void lander::print(void) {
    //  For command line version
    cout << "Height, " << height << " , ";
    cout << "Y-Velocity:, " << Yvelocity << " , ";
    cout << "X-Position:, " << xPosition << " , ";
    cout << "X-Velocity:, " << Xvelocity << " , ";
    cout << "Wind:, " << WIND << " , ";
    cout << "Fuel:, " << fuel << " , ";
    cout << "Burn:, " << burn << " , ";
    cout << "Thrust:, " << thrust << " , " << endl;
}