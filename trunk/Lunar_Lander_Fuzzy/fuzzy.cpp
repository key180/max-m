/* 
 * File:   fuzzy.cpp
 * Author: Paul
 * 
 * Created on April 22, 2012, 1:30 PM
 */
const float MIN_SAFE_X = -0.2;
const float MAX_SAFE_X = 0.2;
const float MAX_SAFE_LANDING_SPEED = -4.0;
const float MAXSPD = MAX_SAFE_LANDING_SPEED;

#include "fuzzy.h"

fuzzy::fuzzy() {
}


fuzzy::fuzzy(const fuzzy& orig) {
}

fuzzy::~fuzzy() {
}


FuzzyXpos::FuzzyXpos(){
    //initialize to zero
    left = 0;
    right = 0;
}
void FuzzyXpos::FuzzifyInput(float pos_input){
        //input a x position's float value then assign the corresponding fuzzy set values
        if (pos_input <= MIN_SAFE_X){
            left = 1;
        }
        if (pos_input >= MAX_SAFE_X){
            right = 1;
        }
        if (pos_input > MIN_SAFE_X && pos_input < 0){
            left = (0 - pos_input) / (0 - MIN_SAFE_X);
        }
        if (pos_input > 0 && pos_input < MAX_SAFE_X){
            right = (0 - pos_input) / (0 - MAX_SAFE_X);
        }
    }

void FuzzyYvel::FuzzifyInput(float Yvel){
    //take float input and fill fuzzy sets 0 to 1

    if (Yvel <= MAXSPD){
        fast = 1;
    }
    if (Yvel > MAXSPD && Yvel < MAXSPD + 1){
        fast = MAXSPD + 1 - Yvel; //a ramp from -3.0 to -4.0 (maxsp = 4)
        safe = Yvel - MAXSPD;
    }
    if (Yvel >= MAXSPD + 1 && Yvel <= -1.0) {
        safe = 1;
    }
    if (Yvel > -1.0 && Yvel < 0){
        safe = -Yvel;
    }
}

FuzzyYvel::FuzzyYvel(){
    safe = 0;
    fast = 0;
}
