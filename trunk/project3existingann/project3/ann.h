/* 
 * File:   ann.h
 * Author: mcki4229
 *
 * Artificial Neural Network
 * 6 inputs: height, xPosition, Yvelocity, Xvelocity, wind, and fuel. 
 * 2 outputs: burn, thrust
 * 
 * Set weights by hand to start, but then train and analyze 
 * 
 * Created on April 2, 2012, 10:05 AM
 * 
 * 4/2 Node object outline
 */

#ifndef ANN_H
#define	ANN_H

class ann { //Artificial Neural Network Node
public:
    ann();
    ann(const ann& orig);
    virtual ~ann();

    float output;
    float error;
    float* weight;
    float* delta;

private:

};



#endif	/* ANN_H */

