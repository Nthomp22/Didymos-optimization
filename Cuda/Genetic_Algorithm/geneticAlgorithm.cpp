#include "geneticAlgorithm.h"

void selectWinners(Individual* pool, int selectionSize, Individual* survivors) {
    for(int i = 0; i < selectionSize; i++) {
        if (greaterInd(pool[2*i],pool[(2*i)+1])) {
            survivors[i] = pool[2*i];
        }
        else {
            survivors[i] = pool[(2*i)+1];
        }
    }   
}

double posRange(Individual* pool, int size) {
    return abs(pool[0].posDiff - pool[size-1].posDiff);
}

double velRange(Individual* pool, int size) {
    return abs(pool[0].velDiff - pool[size-1].velDiff);
}

bool converge(Individual* pool, int size) {
    return posConverge(pool, size) && velConverge(pool, size);
}

bool posConverge(Individual* pool, int size) {
    if (pool[size-1].posDiff < POSITION_THRESH) {
        if (posRange(pool, size)/pool[0].posDiff < CONVG_TOL) {
            return true;
        }
        else return false;
    }
    else return false;
}

bool velConverge(Individual* pool, int size) {
    if (pool[size-1].velDiff > SPEED_THRESH) {
        if (velRange(pool, size)/pool[0].velDiff < CONVG_TOL) {
            return true;
        }
        else return false;
    }
    else return false;
}

void reAnneal(Individual* pool, int size, double amax, double amin) {
    std::cout << "Re-annealing: [";
    int i = 0;
    if (trunc(pool[0].posDiff/ANNEAL_SCALE) == 0) {
        std::cout << ">";
        i++;
        if (trunc(pool[size-1].posDiff/ANNEAL_SCALE) == 0) {
            std::cout << ">";
            i++;
            if (trunc(pool[0].velDiff/ANNEAL_SCALE) == 0) {
                std::cout << ">";
                i++;
                if (trunc(pool[size-1].velDiff/ANNEAL_SCALE) == 0) {
                    std::cout << ">";
                    i++;
                }
            }
        }
    }
    std::cout << "]\n";
    amax *= pow(2,i);
    amin *= pow(2,i);
    return;
}