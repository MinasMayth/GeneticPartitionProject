/* file        : Testing.c
 * authors     : Samy Hashim (s.t.a.hashim@student.rug.nl)
 *             : Alexander Vogt (a.n.vogt@student.rug.nl)
 * date        : Due 07/11/2021
*/

#include "Testing.h"
#include "GeneticPartitionCore.h"

bool adequateT2 (int t2) {
    printf("t2 = %d\n", t2);

    simulationConfiguration.iterations = t2;
    int results[T2_CONFIG];
    set_type set;
    generateInitialTowerSet(set, true);

    for(int x=0; x< T2_CONFIG; x++){
        if(x%(T2_CONFIG/50) == 0){
            printf("|");
            fflush(stdout);
        }
        simulateEvolution(set, results + x);
    }
    printf("|\n");



    int smallestNumber = 1;
    int smallestValue = results[0];

    for (int i = 0; i < T2_CONFIG ; i++){
        if (smallestValue == results[i]) {
            ++smallestNumber;

        } else if (smallestValue < results[i]){
            smallestNumber = 1;
            smallestValue = results[i];
        } else {
            continue ;
        }
    }

    printf("Similarity : %d% \n" , (int)(smallestNumber * 100)/ T2_CONFIG);

    if (smallestNumber >= MINIMUM_PER_SIMULATION_T2 * T2_CONFIG) {
        return true;
    } else {
        return false;

    }
}

void findT2 () {

    simulationConfiguration.numberOfMutations = NUMBER_OF_MUTATIONS;
    simulationConfiguration.numberOfCrossOvers = NUMBER_OF_CROSSOVERS;
    simulationConfiguration.numberOfReplacedChromosomes = NUMBER_OF_CHROMOSOMES_REPLACED;

    int t2 = 1;
    while (!adequateT2(t2))
    {
       t2 = t2 * 10;
    }

    int refineT2;
    for (int i = 0; i < REFINE_T2; i++){
        if (adequateT2((t2*i) / refineT2)){
            refineT2 = ((t2*i) / refineT2 );
        }
    }
    printf("t2 used of %d\n",refineT2);
}

//Might be something missing

