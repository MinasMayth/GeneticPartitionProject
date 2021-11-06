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

}

void printOutput(int *set, int convergeStatus, chromo_type chromo) {

}

void printChromosome(chromo_type chromo) {

}

void printDivider(int length) {
    for(int x=0; x < length; x++){
        printf("%c", DIVIDER_CHARACTER);
    }
    printf("\n");

}
