// Didymos Optimization Project using CUDA and a genetic algorithm

#include "../constants.h" //used for wetMass
#include "../Earth_calculations/orbitalMotion.h" //used for trajectory() and trajectoryPrint()
#include "../Earth_calculations/earthInfo.h"
#include "../Runge_Kutta/runge_kuttaCUDA.cuh" //for testing rk4simple

#include <iostream> // cout
#include <iomanip> //used for setw(), sets spaces between values output
#include <time.h> //for seeding the random number generator
#include <random>
#include <chrono>
#include <climits> // for INT_MAX

double optimize(const int numThreads, const int blockThreads) {
    double calcPerS = 0;
    time_t timeSeed = time(0); // Current set to 0 instead of time(0) to ideally help in testing the algorithm
    std::cout << "Seed for this run: " << timeSeed << std::endl; // note there are other mt_rands in the code that use different seeds
    std::cout << "------------------------------------------------------------------------" << std::endl;
    std::mt19937_64 mt_rand(timeSeed);

    // input parameters for rk4Simple which are the same for each thread
    double timeInitial = 0; // the starting time of the trip is always defined as zero   
    double absTol = RK_TOL; // the tolerance is a constant number that is shared amongst all runs
    double stepSize = (orbitalPeriod - timeInitial) / MAX_NUMSTEPS; // the starting step size- same for each run- note that the current step size varies throughout each run


    Individual *inputParameters = new Individual[numThreads]; // contains all input parameters besides those which are always common amongst every thread

    const int numStarts = 14; // the number of different sets of starting parameters in the input file

    std::ifstream starts;
    starts.open("../optimizedVector.bin", std::ifstream::in|std::ios::binary); // a file containing the final parameters of converged results from CPU calculations

    double startDoubles;

    // sort the data into 2 dimensions
    // one row is one set of starting parameters
    // each column is a specific variable:
    //    0-6 gamma
    //    7-9 tau
    //    10-12 launch angles
    //    13 trip time
    //    14-19 coast
    double arrayCPU[numStarts][OPTIM_VARS];
    for (int i = 0; i < OPTIM_VARS; i++) { // rows
        for (int j = 0; j < numStarts; j++) { // columns
            starts.read( reinterpret_cast<char*>( &startDoubles ), sizeof startDoubles );
            arrayCPU[j][i] = startDoubles;
        }
    }
    starts.close();

     // set every thread's input parameters to a set of final values from CPU calculations for use as a good starting point
    for (int i = 0; i < numThreads; i++) {
        int row = mt_rand() % numStarts;

        double tripTime = arrayCPU[row][13];

        double alpha = arrayCPU[row][10];

        double beta = arrayCPU[row][11];

        double zeta = arrayCPU[row][12];

        coefficients<double> testcoeff;
        for (int j = 0; j < testcoeff.gammaSize; j++) {
            testcoeff.gamma[j] = arrayCPU[row][j];
        }

        for (int j = 0; j < testcoeff.tauSize; j++) {
            testcoeff.tau[j] =  arrayCPU[row][j+7];
        }

        for (int j = 0; j < testcoeff.coastSize; j++) {
            testcoeff.coast[j] = arrayCPU[row][j+14];
        }

        rkParameters<double> example(tripTime, alpha, beta, zeta, testcoeff); 

        inputParameters[i].startParams = example;
    }

    // set every thread's input parameters to random values within a reasonable range
    /*
    for(int i = 0; i < numThreads; i++){ 
        double tripTime = 365*24*3600*(std::rand() % 10001 / 10000.0 + 1.0);
        double alpha = (mt_rand() % 629) / 100.0 - 3.14;
        double beta = (mt_rand() % 629) / 100.0 - 3.14;
        double zeta = (mt_rand() % 315) / 100.0 - 1.57;

        coefficients<double> testcoeff;
        for(int j = 0; j < testcoeff.gammaSize; j++){
            testcoeff.gamma[j] = mt_rand() % 201/10.0 - 10.0;
        }
        for(int j = 0; j < testcoeff.tauSize; j++){
            testcoeff.tau[j] = mt_rand() % 201/10.0 - 10.0;
        }
        for(int j = 0; j < testcoeff.coastSize; j++){
            testcoeff.coast[j] = mt_rand() % 201/10.0 - 10.0;
        }
    
        rkParameters<double> example(tripTime, alpha, beta, zeta, testcoeff); 

        inputParameters[i].startParams = example;
    }
    */


    Individual *survivors = new Individual[SURVIVOR_COUNT]; // stores the winners of the head-to-head competition
    int newInd = numThreads; // the whole population is new the first time through the loop

    // setup output of results onto a .csv file
    std::ofstream generationPerformance;
    generationPerformance.open("generations.csv");
    generationPerformance << "Gen #" << "," << "BestPosDiff" << "," << "BestVelDiff" << "," << "WorstPosDiff" << "," << "WorstVelDiff" << "\n";
    
    unsigned int generation = 0;    // A counter for number of generations calculated
    

    // A while loop that continues until it is determined that the pool of inputParameters has converged
    
    double currentDistance;

    double tolerance = POSITION_THRESH; // Tolerance for what is an acceptable solution (currently just POSITION_THRESH which is furthest distance from the target allowed)

    do {
        // initialize positions for the new individuals starting at the index of the first new one and going to the end of the array
        initializePosition(inputParameters + (numThreads - newInd), newInd);

        callRK(newInd, blockThreads, inputParameters + (numThreads - newInd), timeInitial, stepSize, absTol, calcPerS); // calculate trajectories for new individuals

        // if we got bad results reset the Individual to random starting values (it may still be used for crossover) and set the final position to be way off so it gets replaced by a new Individual
        for (int k = 0; k < numThreads; k++) { 
            if (isnan(inputParameters[k].finalPos.r) || isnan(inputParameters[k].finalPos.theta) || isnan(inputParameters[k].finalPos.z) 
                 || isnan(inputParameters[k].finalPos.vr) || isnan(inputParameters[k].finalPos.vtheta) || isnan(inputParameters[k].finalPos.vz)){
                
                std::cout << std::endl << std::endl << "NAN FOUND" << std::endl << std::endl;

                double tripTime = 365*24*3600*(std::rand() % 10001 / 10000.0 + 1.0);
                double alpha = (mt_rand() % 629) / 100.0 - 3.14;
                double beta = (mt_rand() % 629) / 100.0 - 3.14;
                double zeta = (mt_rand() % 315) / 100.0 - 1.57;
        
                coefficients<double> testcoeff;
                for (int j = 0; j < testcoeff.gammaSize; j++) {
                    testcoeff.gamma[j] = mt_rand() % 201/10.0 - 10.0;
                }
                for (int j = 0; j < testcoeff.tauSize; j++) {
                    testcoeff.tau[j] = mt_rand() % 201/10.0 - 10.0;
                }
                for (int j = 0; j < testcoeff.coastSize; j++) {
                    testcoeff.coast[j] = mt_rand() % 201/10.0 - 10.0;
                }
            
                rkParameters<double> example(tripTime, alpha, beta, zeta, testcoeff); 
        
                inputParameters[k].startParams = example;

                inputParameters[k].posDiff = 1.0e10;
                inputParameters[k].velDiff = 0.0;
             }
        }

        std::shuffle(inputParameters, inputParameters + numThreads, mt_rand); // shuffle the Individiuals to use random members for the competition
        selectWinners(inputParameters, SURVIVOR_COUNT, survivors); // Choose which individuals are in survivors, not necessarrily only the best ones
        std::sort(inputParameters, inputParameters + numThreads, betterInd); // put the individuals in order so we can replace the worst ones

        // Display a '.' to the terminal to show that a generation has been calculated
        // if it is not the 50th generation this serves to show that a generation was calculated and survivors selected
        // This also serves to visually seperate the generation display on the terminal screen
        std::cout << '.';

        // Display and print Individuals' pos and vel difference every 200 generations to terminal
        if (generation % 200 == 0) { 
            // Display the best and worst Individuals in this generation
            std::cout << '\n';
            std::cout << "generation: " << generation << std::endl;
            std::cout << "best:" << std::endl;
            std::cout << "\tposDiff: " << inputParameters[0].posDiff << std::endl;
            std::cout << "\tvelDiff: " << inputParameters[0].velDiff << std::endl;
            std::cout << "\tcost: "    << inputParameters[0].getCost() << std::endl;
            std::cout << "worst:" << std::endl;
            std::cout << "\tposDiff: " << inputParameters[numThreads - 1].posDiff << std::endl;
            std::cout << "\tvelDiff: " << inputParameters[numThreads - 1].velDiff << std::endl;
            std::cout << "\tcost: "    << inputParameters[numThreads - 1].getCost() << std::endl;
            
            
        }

        // Write the best and worst Individuals in every 100 generations into a csv file to view progress over generations
        if (generation % 100 == 0) {
            generationPerformance << generation << "," <<inputParameters[0].posDiff << ","  << inputParameters[0].velDiff << "," << inputParameters[numThreads - 1].posDiff << "," << inputParameters[numThreads - 1].velDiff << "\n";
        }

        // Calculate how far the pool is from the ideal cost value (0)
        currentDistance = inputParameters[0].posDiff; // Change this later to take into account more than just the best individual


        // the annealing rate passed in is scaled between ANNEAL_MAX and ANNEAL_MIN, dependent on the ratio between the tolerance and current distance from the tolerance
        double new_anneal =  ANNEAL_MAX - tolerance / currentDistance * (ANNEAL_MAX - ANNEAL_MIN);

        // Create a new generation
        newInd = crossover(survivors, inputParameters, SURVIVOR_COUNT, numThreads, new_anneal);
        ++generation;
        // If the current distance is still higher than the tolerance we find acceptable, perform the loop again
    } while (currentDistance > tolerance);


    
    // output the best Individuals of the final generation, using writeTrajectoryToFile()
    // Files outputted allows plotting of solutions in matlab
    double *start = new double[OPTIM_VARS];
    double cost = 0;
    // Output to excel
    generationPerformance << generation << "," <<inputParameters[0].posDiff << ","  << inputParameters[0].velDiff << "," << inputParameters[numThreads - 1].posDiff << "," << inputParameters[numThreads - 1].velDiff << "\n";

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < inputParameters[i].startParams.coeff.gammaSize; j++) {
            start[GAMMA_OFFSET + j] = inputParameters[i].startParams.coeff.gamma[j];
        }
        for (int j = 0; j < inputParameters[i].startParams.coeff.tauSize; j++) {
            start[TAU_OFFSET + j] = inputParameters[i].startParams.coeff.tau[j];
        }
        for (int j = 0; j < inputParameters[i].startParams.coeff.coastSize; j++) {
            start[COAST_OFFSET + j] = inputParameters[i].startParams.coeff.coast[j];
        }

        start[TRIPTIME_OFFSET] = inputParameters[i].startParams.tripTime;
        start[ALPHA_OFFSET] = inputParameters[i].startParams.alpha;
        start[BETA_OFFSET] = inputParameters[i].startParams.beta;
        start[ZETA_OFFSET] = inputParameters[i].startParams.zeta;

        cost = inputParameters[i].posDiff; // just look at position difference here for now
        // could instead use a ratio between position and velocity differnce as done in comparison of Individuals
        writeTrajectoryToFile(start, cost, i + 1);
    }


    generationPerformance.close();

    delete [] inputParameters;
    delete [] survivors;

    return calcPerS;
}

int main () {
    // display GPU properties and ensure we are using the right one
    cudaDeviceProp prop;
    cudaGetDeviceProperties(&prop, 0);
    std::cout << "Device Number: 0 \n";
    std::cout << "- Device name: " << prop.name << std::endl;
    cudaSetDevice(0);
    
    // pre-calculate a table of Earth's position within possible mission time range
    //----------------------------------------------------------------
    // Define variables to be passed into EarthInfo
    double startTime = 15778800; // 0.5 year (s)
    double endTime = 78894000; // 2.5 years (s)
    double timeRes = 3600; // (s) position of earth is calculated for every hour

    launchCon = new EarthInfo(startTime, endTime, timeRes); // a global variable to hold Earth's position over time
    //----------------------------------------------------------------

    int blockThreads = 32;
    int numThreads = 2880; // the number of cores on a Tesla k40
    //int numThreads = 1920; // 384 cores on K620 * 5 = 1920

    //std::ofstream efficiencyGraph; // for viewing how many runge-kuttas ran per second for each combination of threads per block and total threads 
    //efficiencyGraph.open("efficiencyGraph.csv");
    std::cout << std::endl << "running optimize() with " << blockThreads << " threads per block and " << numThreads << " total threads" << std::endl;
    
    optimize(numThreads, blockThreads);

    //efficiencyGraph << blockThreads << "," << numThreads << "," << calcPerS  << "\n";
    //efficiencyGraph.close();
    
    delete launchCon;

    return 0;
}
