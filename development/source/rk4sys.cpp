
#include <vector>
#include "rk4sys.h"
#include <iostream>

/* fourth-order RUnge-Kutta for a system of ODEs
-integrates a system of ODEs with fourth-order RK method

Input:
double timeInitial and double timeFinal; initial and final times for the computation,
elements y0: initial values of dependent variables
stepSize: the difference between times
output:
returns: y - solutions of dependent variables
*/ 
<<<<<<< Updated upstream
elements* rk4sys(double timeInitial, double timeFinal, elements y0, double stepSize){
    

    // Define the max number of iterations
    int nMax = (timeFinal-timeInitial)/stepSize;

    // How to allocate memory in C
    // elements* y;
    //  y = (elements *)malloc(sizeOf(elements)*nMax);
    elements* y;
    y = new elements[nMax];
    // Set the first element of the solution vector to the initial conditions
    y[0] = y0;
    
    for(int n=0;n<=nMax+1;n++)
    {
        // If we required the time
        // time = stepSize*n
        
<<<<<<< Updated upstream
        // Variables for Runge-Kutta
        elements k1, k2, k3, k4, ymid;
       
       // Runge-Kutta algorithm

            k1 = calc_k(y[n],stepSize/2);
            ymid = calc_ymid(ymid,stepSize,k1);
            k2 = calc_k(y0,stepSize/2);
            ymid = calc_ymid(ymid,stepSize,k2);
            k3 = calc_k(ymid,stepSize);
            ymid = calc_ymid(ymid,stepSize,k3);
		    k4 = calc_k(ymid, stepSize);

            // Add weighted slopes
			elements phi = (k1 + (k2 + k3) * 2 + k4) / 6; // calculate phi for each element
            y[n+1] = y[n] + phi * stepSize;
        std::cout<<y[n].r<<std::endl;
        std::cout<<k1.r<<std::endl;
=======
        if(hh > stepSize)
            hh = stepSize;

            while(true){
                if((tt + hh) > tend)
                    hh = tend - tt;

                //MATH
                elements k1, k2, k3, k4, ymid;
                
				ymid = y0;
                k1 = calc_k(y0,hh/2);
                ymid = calc_ymid(ymid,hh,k1);
                k2 = calc_k(y0,hh/2);
                ymid = calc_ymid(ymid,hh,k2);
                k3 = calc_k(ymid,hh);
                ymid = calc_ymid(ymid,hh,k3);
				k4 = calc_k(ymid, hh);




				//add weighted slopes
				elements phi = (k1 + (k2 + k3) * 2 + k4) / 6; // calculate phi for each element
                y[j+1] = y[j] + phi * hh;

                //counter
                tt = tt + hh;
                j++;

                if (tt >= tend)
                    break;
            }

            np++;
           // t[np] = tt;
            yp[np] = y[j];
>>>>>>> Stashed changes

    }

<<<<<<< Updated upstream
    return y;
}
=======
void testKCalc(elements y0){
    elements k1, k2, k3, k4, ymid;
    double hh = 1.330764020184744e+05;

	ymid = y0;
    k1 = calc_k(y0,hh/2);
    elements ymid1 = calc_ymid(ymid,hh/2,k1);
    k2 = calc_k(ymid1,hh/2);
    elements ymid2 = calc_ymid(ymid1,hh/2,k2);
    k3 = calc_k(ymid2,hh);
    elements ymid3 = calc_ymid(ymid2,hh,k3);
	k4 = calc_k(ymid3, hh);

    std::cout << "k1.r " << k1.r << "\n";
    std::cout << "k1.theta " << k1.theta << "\n";
    std::cout << "k1.z " << k1.z << "\n";
    std::cout << "k1.vr " << k1.vr << "\n";
    std::cout << "k1.vtheta " << k1.vtheta << "\n";
    std::cout << "k1.vz " << k1.vz << "\n\n";

    std::cout << "k2.r " << k2.r << "\n";
    std::cout << "k2.theta " << k2.theta << "\n";
    std::cout << "k2.z " << k2.z << "\n";
    std::cout << "k2.vr " << k2.vr << "\n";
    std::cout << "k2.vtheta " << k2.vtheta << "\n";
    std::cout << "k2.vz " << k2.vz << "\n\n";
    
    std::cout << "k3.r " << k3.r << "\n";
    std::cout << "k3.theta " << k3.theta << "\n";
    std::cout << "k3.z " << k3.z << "\n";
    std::cout << "k3.vr " << k3.vr << "\n";
    std::cout << "k3.vtheta " << k3.vtheta << "\n";
    std::cout << "k3.vz " << k3.vz << "\n\n";
    
    std::cout << "k4.r " << k4.r << "\n";
    std::cout << "k4.theta " << k4.theta << "\n";
    std::cout << "k4.z " << k4.z << "\n";
    std::cout << "k4.vr " << k4.vr << "\n";
    std::cout << "k4.vtheta " << k4.vtheta << "\n";
    std::cout << "k4.vz " << k4.vz << "\n";
}

#endif // !rk4sys_cpp
>>>>>>> Stashed changes
