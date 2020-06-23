#ifndef thruster_h
#define thruster_h
#include "coefficients.h"
#include "config.h"

// file path for all data used in this file: \\fs1\phys\sankaranResearch\2019-Lauren-Mateo\Thruster

// sets starting values as given in the 2017 data excel sheet
template <class T> struct thruster {
    T m_Dot; // fuel flow rate
    int type; // type of thruster
    T P0; // inital power in
    T m_Dot0; // initial m_Dot

    double coastThreshold; // threshold to activate thruster

    __host__ __device__ thruster<T>(geneticConstants & gConfig);

    //overload the stream output for elements used for writing to a file
    template <class T> friend std::ostream & operator<<(std::ostream & Str, const thruster<T> & e); 

// Evaluates the spacecraft's effciency for a certian iteration based off of a best fit line from file above of eff vs. power in (W).
// Parameters:
//         Pin: Given a certian value of power in to the spacecraft, a specific efficiency will be calculated for an iteration.
// output: spacecraft's effciency for a certian iteration
   __host__ __device__ T calc_eff(const T & Pin);

// Evaluates the spacecraft's fuel flow rate (mDot) for a certian iteration based off of "if statements".
// Parameters:
//         Pin: Given a certian value of power in to the spacecraft, a certian fuel flow rate will be set for an iteration.
// output: spacecraft's mDot for a certian iteration
    __host__ __device__ void calc_m_Dot(const T & Pin);

    // thruster type enumeration
    enum THRUST_TYPE {
        NO_THRUST = 0,
        NEXT_C = 1
    };
    
    private:
    T NEXTP0 =7330; // initial power (W)
    T NEXTm_Dot0 = 5.73E-06; // inital fuel flow rate (kg/s)

};

#include "thruster.cpp"
#endif
