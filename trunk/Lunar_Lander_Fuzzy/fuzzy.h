/* 
 * File:   fuzzy.h
 * Author: Paul
 *
 * Created on April 22, 2012, 1:30 PM
 */

#ifndef FUZZY_H
#define	FUZZY_H



class fuzzy {
public:
    float burn;
    float thrust;
    

        
    
    fuzzy();
    fuzzy(const fuzzy& orig);
    virtual ~fuzzy();
private:

};

class FuzzyHeight{
public:
    double veryclose,
            close,
            far;
    void FuzzifyInput(double height_input){
        //input a height as it's value then assign fuzzy sets values
        double crossovers[4] = {0,2,10,150};
    }
};

class FuzzyXpos{
public:
    double left,
            center,
            right;
    
    void FuzzifyInput(double pos_input){
        //input a x position's double value then assign the corresponding fuzzy set values
        if (pos_input <= MIN_SAFE_X){
            left = 1;
            
        }
        
    }
};


#endif	/* FUZZY_H */