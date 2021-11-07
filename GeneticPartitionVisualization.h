//
// Created by samya on 06/11/2021.
//

#ifndef GENETICPARTITION_GENETICPARTITIONVISUALIZATION_H
#define GENETICPARTITION_GENETICPARTITIONVISUALIZATION_H


#include "GeneticPartitionCore.h"
#include "GeneticPartitionConfigurationSettings.h"
#include <stdbool.h>

// Output constants
#define DIVIDER_CHARACTER '-'
#define DIVIDER_LENGTH 80

void printOriginalSet(set_type set);
void printTowerSets(set_type set, chromo_type chromo);
void printTowerSet(set_type set, bool chosenSet, chromo_type chromo);


void printOutput(set_type set, int convergeStatus, chromo_type chromo);
void printChromosome(chromo_type chromo);

void printDivider(int length);


#endif //GENETICPARTITION_GENETICPARTITIONVISUALIZATION_H
