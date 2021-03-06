/* file        : GeneticPartitionConfigurationSettings.h
 * authors     : Samy Hashim (s.t.a.hashim@student.rug.nl)
 *             : Alexander Vogt (a.n.vogt@student.rug.nl)
 * date        : Due 05/11/2021
*/

/*
 * Function declarations, constant and types used during the simulation
 */


#ifndef GENETICPARTITION_GENETICPARTITIONCONFIGURATIONSETTINGS_H
#define GENETICPARTITION_GENETICPARTITIONCONFIGURATIONSETTINGS_H

// Libraries

#include <stdio.h>
#include <stdbool.h>

// Initial constants

#define NUMBER_OF_BlOCKS 20
#define LENGTH_OF_CHROMOSOME NUMBER_OF_BlOCKS

//Program Configuration

#define NUMBER_OF_CROSSOVERS 5
#define NUMBER_OF_MUTATIONS 20
#define NUMBER_OF_CHROMOSOMES_REPLACED 2

// Termination

#define POPULATION_SIZE 10
#define MAX_T2 500000
#define MAX_T1 (10 * MAX_T2)

// The use of a struct allows us to test multiple different configurations

typedef struct {
    int numberOfMutations;
    int numberOfReplacedChromosomes;
    int numberOfCrossOvers;
    int iterations;
} simulationConfigurationType;

simulationConfigurationType simulationSettings;

//Function

void printConfiguration(simulationConfigurationType simulationConfiguration);

#endif //GENETICPARTITION_GENETICPARTITIONCONFIGURATIONSETTINGS_H
