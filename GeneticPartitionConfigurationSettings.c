/* file        : GeneticPartitionConfigurationSettings.c
 * authors     : Samy Hashim (s.t.a.hashim@student.rug.nl)
 *             : Alexander Vogt (a.n.vogt@student.rug.nl)
 * date        : Due 05/11/2021
*/

#include "GeneticPartitionConfigurationSettings.h"

// This function prints out the configuration values used during the simulation

void printConfiguration(simulationConfigurationType simulationConfiguration ){
    printf("The configuration of the simulation \n");

    printf("Number of Mutations : %d, Number of Cross-Overs : %d, Number of replaced Chromosomes : %d , Time : %d \n\n",
           simulationConfiguration.numberOfMutations,
           simulationConfiguration.numberOfCrossOvers,
           simulationConfiguration.numberOfReplacedChromosomes,
           simulationConfiguration.iterations
           );
}