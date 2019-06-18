#ifndef rk4sys_h
#define rk4sys_h
#include "ode45.h" // Utility functions for calc_k()


// Three variations of fifth-order Runge-Kutta algorthim for system of ODEs defined in ODE45.h
// 1. rk4sys
// 2. rk4Simple
// 3. rk4Reverse

// Using adaptive time stepping  
// Parameters: 
//      timeInitial: start time (s)
//      timeFinal: end time (s)
//      times:an array that contains the time for each data point
//      y0: initial conditions (position,velocity)
//      stepSize: first time interval between data points (s)
//      y: an array which contains the soultion to the dependent variable
//      absTol: Sets the error tolerence for Runge-Kutta
//      coeff: passes the structure containing the fourier coefficients for gamma and tau
//      accel: constant value of spacecraft's acceleration (au/s^2)
//      gamma: an array which contains all gamma values for a given run
//      tau: an array which contains all tau values for a given run


// 1.
    // Extra parameters:
    //      lastStep: returns the index of the last element of y
    // Output: A dynamic array of position and velocity sets, last entry is final conditions
template <class T> void rk4sys(const T & timeInitial, const T & timeFinal, T *times, const elements<T> & y0, 
T stepSize, elements<T> *y, const T & absTol, coefficients<T> coeff, const T & accel, T *gamma, T *tau, int & lastStep);

// 2.
    // Output: writes in y the final position  of the spacecraft
template <class T> void rk4Simple(const T & timeInitial, const T & timeFinal, const elements<T> & y0, 
T stepSize, elements<T> &y, const T & absTol, coefficients<T> coeff, const T & accel);

//3.
    // Comment on stepsize: Expected to be negative due to reverse integration
    // Output: writes in y the initial position of earth at the time of spacecraft launch based on an optimized trip time
    // To improve efficiency, the rk4 with single returns were split into two functions to avoid "if" statements, which are not prefered in CUDA.
template <class T> void rk4Reverse(const T & timeInitial, const T & timeFinal, const elements<T> & y0, 
T stepSize, elements<T> &y, const T & absTol, coefficients<T> coeff, const T & accel);


/**********************************************************************************************************************************/

// Calculates the scaling factor for the stepSize
// Parameters:
//      previous: The previous result of the Runge-Kutta 
//      difference: The new result minus the previous result (v-u)
//      absTol: Sets the error tolerence for Runge-Kutta
//      stepSize: time interval between data points (s)
// Output: Unitless scaling coefficient which changes the time step each iteration
template <class T> T calc_scalingFactor(const elements<T> & previous , const elements<T> & difference, const T & absTol, T & stepSize);

#include "rk4sys.cpp"
#endif