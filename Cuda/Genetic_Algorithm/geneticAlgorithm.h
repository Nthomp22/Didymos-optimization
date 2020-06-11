#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include "individuals.h"
#include "gaConstants.h"


// takes Individuals from the pool to compete in a head-to-head competition
// input: 
    // pool: the overall population (should be in randomized order)
    // selectionSize: the number of survivors to return
// output: 
    //survivors: the winners of the competition
void selectWinners(Individual* pool, int selectionSize, Individual* survivors);

// Calculates the range of positions from the asteroid within the pool
// Input:
    // pool: the entire generation (must already be sorted)
// Output:
    // costRange: the difference in cost function between the least and greatest Individuals
double posCost(Individual* pool);

// Calculates the range of velocities from the asteroid within the pool
// Input:
    // pool: the entire generation (must already be sorted)
// Output:
    // costRange: the difference in cost function between the least and greatest Individuals
double velCost(Individual* pool);

// Determines whether the pool meets requirements for convergence
// Input:
    // pool: the entire generation (must already be sorted)
// Output:
    // convgFlag: Boolean indicating whether the pool has converged
bool converge(Individual* pool);

// Determines whether the pools' posDiffs have converged
// Input:
    // pool: the entire generation (must already be sorted)
// Output:
    // convgFlag: Boolean indicating whether posDiffs have converged
bool posConverge(Individual* pool);

// Determines whether the pool's velDiffs have converged
// Input:
    // pool: the entire generation (must already be sorted)
// Output:
    // convgFlag: Boolean indicating whether velDiffs have converged
bool velConverge(Individual* pool);

#include "geneticAlgorithm.cpp"
#endif