/* file        : Testing.h
 * authors     : Samy Hashim (s.t.a.hashim@student.rug.nl)
 *             : Alexander Vogt (a.n.vogt@student.rug.nl)
 * date        : Due 07/11/2021
*/

#ifndef GENETICPARTITION_TESTING_H
#define GENETICPARTITION_TESTING_H

//Libraries
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>


#include "GeneticPartitionConfigurationSettings.h"
#include "GeneticPartitionCore.h"

//Constants

#define TEST 0

#define REFINE_T2 10

#define MINIMUM_PER_SIMULATION_T2 0.8

#define T2_CONFIG 100

//Functions

void findT2();
bool adequateT2 (int t2);


#endif //GENETICPARTITION_TESTING_H
