//
// Created by samya on 06/11/2021.
//

#include "GeneticPartitionVisualization.h"

void printOriginalSet(int *set) {
    for(int x = 0; x<NUMBER_OF_BlOCKS; x++){
        printf("%d", set[x]);
    }
    printf("\n");
}

void printTowerSets(int *set, chromo_type chromo) {
    printf("False set: \n");
    printTowerSet(set, false, chromo);

    printf("True set: \n");
    printTowerSet(set, true, chromo);
}

void printTowerSet(int *set, bool chosenSet, chromo_type chromo) {
    int sum = 0;
    printf('{');
    for(int x=0; x<LENGTH_OF_CHROMOSOME; x++){
        if(chosenSet == chromo.genes[x]){
            if(x != LENGTH_OF_CHROMOSOME-1){
                printf("%d, ", set[x]);
            }else{
                printf("%d", set[x]);
            }
            sum += set[x];

        }
    }
    printf('}');
    printf("\nsum = %d", sum);

}

void printOutput(int *set, int convergeStatus, chromo_type chromo) {
    switch (convergeStatus) { //nice to be able to use switch like in java for alternating cases here
        case NO_IMPROVEMENTS:
            printf("Most equal distribution of tower blocks found: \n",
                   towerHeightDifference(set, chromo));
            break;
        case SOLUTION:
            //printf("Solution found!\n");
            break;
        case AFTER_MAX_ITER:
            printf("Max iterations reached\n");
            break;
        default:
            break;


    }
    printf("CHROMOSOME: ");
    printChromosome(chromo);
    printDivider(DIVIDER_LENGTH);

    printTowerSets(set, chromo);
    printDivider(DIVIDER_LENGTH);
}

void printChromosome(chromo_type chromo) {
    for(int x=0; x< LENGTH_OF_CHROMOSOME; x++){
        printf("%d", chromo.genes[x]);
    }

}

void printDivider(int length) {
    for(int x=0; x < length; x++){
        printf("%c", DIVIDER_CHARACTER);
    }
    printf("\n");

}
