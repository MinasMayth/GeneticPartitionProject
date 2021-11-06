/* file        : GeneticPartitionConfigurationSimulation.h
 * authors     : Samy Hashim (s.t.a.hashim@student.rug.nl)
 *             : Alexander Vogt (a.n.vogt@student.rug.nl)
 * date        : Due 05/11/2021
*/

/*
 * Function declarations, constant and types used during the simulation
 */


#ifndef GENETICPARTITION_GENETICPARTITIONCONFIGURATIONSIMULATION_H
#define GENETICPARTITION_GENETICPARTITIONCONFIGURATIONSIMULATION_H

// Libraries

#include <stdio.h>
#include <stdbool.h>

// Initial constants

#define NUMBER_OF_BlOCKS 20
#define LENGTH_OF_CHROMOSOME NUMBER_OF_BlOCKS

//Program Configuration

#define NUMBER_OF_CROSSOVERS 5
#define NUMBER_OF_MUTATIONS 15
#define NUMBER_OF_CHROMOSOMES_REPLACED 3

// Termination

#define POPULATION_SIZE 10
#define MAX_TIME 500000
#define MAX_ITERATION (10 * MAX_TIME)

// The use of a struct allows to test multiple different configurations

typedef struct {
    int numberOfMutations;
    int numberOfReplacedChromosomes;
    int numberOfCrossOvers;
    int time;
} simulationConfigurationType;

simulationConfigurationType simulationConfiguration;

//Function

void printConfiguration (simulationConfigurationType simulationConfigurationType simulationConfiguration);

#endif //GENETICPARTITION_GENETICPARTITIONCONFIGURATIONSIMULATION_H
