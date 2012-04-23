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

class FuzzyYvel {
public:
    FuzzyYvel();
    float safe,
            fast;

    void FuzzifyInput(float Yvel);

};

class FuzzyXpos {
public:
    FuzzyXpos();
    float left, // define the two fuzzy sets
    right;

    void FuzzifyInput(float pos_input);
};


#endif	/* FUZZY_H */
