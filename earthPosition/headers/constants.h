#ifndef constants_h
#define constants_h
#include <math.h>

#define earthRadius 1.49598261e11/AU // radius of the earth (au)
#define earthMass 5.9742e24 // mass of the earth (kg)
#define ESOI earthRadius*pow((earthMass/massSun),0.4) // escape sphere of influence (au)
#define C3Energy 4.676e6 // energy of spacecraft at earth escape (m^2/s^2)
#define vEscape sqrt(C3Energy)/AU // magnitude of velocity at earth escape  (au/s)
#define AU 1.49597870691e11// used to convert meters to astronomical units (m) 
#define constG 1.99349603314131e-44 //gravitational constant- used to calculate the gravitational force (AU^3/(s^2 * kg)) 
#define massSun 1.98892e30// mass of the sun (kg)
#define orbitalPeriod 6.653820100923719e+07 // orbital period time of the asteroid (s)

#define MAX_NUMSTEPS 1e9 // The highest precision the runge kutta method is going to use for the first step
#define RK_TOL 1e-12 // The relative/absolute (not sure which one it is) tolerance for the runge kutta algorithm
#define F_MIN 1e-20 // The expected precision for the optimization cost convergance. This number is meant to avoid unnecesary iteration whitin neder _ mead

//final conditions of the asteroid on impact date
#define R_FIN_AST 1.02696822710421 // radial position (au)
#define THETA_FIN_AST 0.238839574416454 // angular postion (rad)
#define Z_FIN_AST -0.0526614832914496 // axial position (au)
#define VR_FIN_AST -2.05295246185041e-08 // radial velocity (au/s)
#define VTHETA_FIN_AST 2.29132593453064e-07 // angular velocity (au/s)
#define VZ_FIN_AST 8.00663905822009e-09 // axial velocity (au/s)

//final conditions of the earth on impact date
#define R_FIN_EARTH 1.00021392223428 // radial position (au)
#define THETA_FIN_EARTH 0.199470650149394 // angular postion (rad)
#define Z_FIN_EARTH -1.54878511585620e-05 // axial position (au)
#define VR_FIN_EARTH -3.32034068725821e-09 // radial velocity (au/s)
#define VTHETA_FIN_EARTH 1.99029138292504e-07 // angular velocity (au/s)
#define VZ_FIN_EARTH -9.71518257891386e-12 // axial velocity (au/s)

//Official DART mission data
#define V_IMPACT 4.399378072e-08 //impact velocity in AU/s

// starting location in the optimization array
#define OPTIM_VARS 16//Number of variables in the optimization
#define GAMMA_ARRAY_SIZE 7 // Length of the array of coefficients for gamma
#define TAU_ARRAY_SIZE 1 // Length of the array of coefficients for tau
#define COAST_ARRAY_SIZE 5 // Length of the array of coefficients for coasting

#define GAMMA_OFFSET 0 // x[0-8] fourth order fourier for in-plane angle
#define TAU_OFFSET 7 // x[9-13] first order fourier for out-of-plane angle
#define ALPHA_OFFSET 8 // x[14] position escape earth angle
#define BETA_OFFSET 9 // x[15] velocity escape earth angle
#define TRIPTIME_OFFSET 10 // x[16] total duration of the trip
#define COAST_OFFSET 11 // x[17-21] second order fourier for coasting determination

// Value at which if the coast output is below it returns acceleration as 0.
#define COAST_THRESHOLD 0.5

// Spacecraft constants
#define DRY_MASS 2700 // mass of spacecraft excluding fuel (kg)
#define WET_MASS 3000 // mass of the spacecraft including fuel (kg)

#endif