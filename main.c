
/*
* file        : main.c
* authors     : Samy Hashim (s.t.a.hashim@student.rug.nl)
*             : Alexander Vogt (a.n.vogt@student.rug.nl)
* date        : Due 07/11/2021
*
* Description:
* Given two sets of positive integers, we create a pair of disjoint sets.
* The union of these two sets must be the original set, and the sum of the
* integers in each set must equal each other.
* We shall use a genetic algorithm to determine these two sets.
*
* Input: _Precisely_ SIZE_ORIGINAL_SET (20) integers, separated by whitespace
*
* Output: The solution chromosome, and how the chromosome leads to the best
* solution it comes to.
*/


#include "GeneticPartitionCore.h"
#include "GeneticPartitionConfigurationSettings.h"
#include "GeneticPartitionVisualization.h"
#include "Testing.h"

int main(){
    time_t time1;
    srand((unsigned int) time(&time1));

    set_type set;
    chromo_type generation[POPULATION_SIZE];

    //findT2(); for testing!

    simulationSettings.numberOfCrossOvers = NUMBER_OF_CROSSOVERS;
    simulationSettings.numberOfReplacedChromosomes = NUMBER_OF_CHROMOSOMES_REPLACED;
    simulationSettings.numberOfMutations = NUMBER_OF_MUTATIONS;
    simulationSettings.iterations = MAX_T2;

    generateInitialTowerSet(set, true);
    int solutionDiff;
    printf("Simulation started...");
    int numberOfIterations = simulateEvolution(set, &solutionDiff);

    printf("\nNumber of iterations: %d", numberOfIterations);

    return 0;
}

