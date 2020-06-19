#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include "../Runge_Kutta/rkParameters.h"
#include "../Motion_Eqns/elements.h"
#include "../constants.h"
#include "../Earth_calculations/earthInfo.h"

// an Individual is a member of the genetric algorithm's population and has set of parameters and resulting position and velocity
struct Individual {
    rkParameters<double> startParams; // input parameters for the run- the unique identifiers of this individual

    elements<double> finalPos; // final position of the spacecraft at end of run

    double posDiff; // difference in position between spacecraft and center of asteroid at end of run
    double velDiff; // difference in velocity between spacecraft and asteroid at end of run

    // get the inital position of the spacecraft according to this Individual's launch time
    void initialize();

    // Calculates a cost value to quantitatively evaluate this Individual
    double getCost();

    // Some comparison operators overloaded to compare individuals by their cost values (determined in getCost())
    bool operator>(Individual &other);
    bool operator<(Individual &other);
    bool operator==(Individual &other);
};

    // returns the amount of weight placed on the posDiff rather than velDiff in comparison of two Individuals
    // output: 0.0 - 1.0
//    double getPosRatio(Individual first, Individual second);

    // compares two individuals, using < operator
    // other is the Individual to be compared to
    // returns true if the first Individual has a higher fitness
//    bool betterInd(Individual first, Individual second);

#include "individuals.cpp"

#endif