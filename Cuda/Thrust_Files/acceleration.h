#ifndef acceleration_h
#define acceleration_h

#include "thruster.h" // used for P0, calc_eff(), and calc_m_Dot()
#include "../Config_Constants/config.h"
// Calculates acceleration of the spacecraft due to thrusting.
// Parameters:
//         radius: current radial position of the spacecraft relative to the sun (au).
//         thrusterType: part of the thruster structure which decides which thruster is being used for a given run.
//              P0: power into the spacecraft measured on earth.
//              calc_eff(): calculates the efficiency of the spacecraft for a given power in.
//              calc_m_Dot(): calculates the fuel flow rate of the spacecraft based on the power in.
//         massExpelled: recalculated every time the function is called to update the current mass of fuel expended during the trip.
//         deltaT: stepsize for a given iteration, used in the calculation of massExpelled.
//         thrusting: evaluated in calc_coast() to determine whether calc_accel() will be called.
//         wetMass: mass of the spacecraft including the fuel (optimized).
// output: acceleration of the spacecraft due to thrusting.

template <class T> __host__ __device__ T calc_accel(const T & radius, const T & z, thruster<T> & thrusterType, T & massExpelled, const T & deltaT, const bool & thrusting, const T & wetMass, const cudaConstants* cConstants);

#include "acceleration.cpp"
#endif