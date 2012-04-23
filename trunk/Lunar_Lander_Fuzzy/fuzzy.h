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
        if input
        
        
    }
};

class FuzzyXpos{
public:
    double left,
            center,
            right;
};
#endif	/* FUZZY_H */