/* file        : GeneticPartitionCore.c
 * authors     : Samy Hashim (s.t.a.hashim@student.rug.nl)
 *             : Alexander Vogt (a.n.vogt@student.rug.nl)
 * date        : Due 05/11/2021
*/
#include "GeneticPartitionCore.h"
#include "stdbool.h"

/*
 * Methods used for the partition problem
 */

void readInitialDataset(set_type set, bool automatic){
    if(automatic){
        for(int i=0; i < popSize; i++){
            set[i] = rand() % AUTO_MAX;
        }

        printf("Initial set generated: \n");
        for(int i = 0; i < popSize; i++) {
            printf("%d ", set[i]);
            printf("\n");
        }

    }else{
        int spaceLeft = INT_MAX;
        for(int i=0; i < numBlocks; i++) {
            scanf("%d", set + i);
            if (set[i] <= 0) {
                printf("ERROR: You have entered a negative value. This is not allowed.\n");
                exit(-1);
            }if(set[i] > spaceLeft){
                printf("These values are to large for the code to handle.");
            }else{
                spaceLeft -= set[i];
            }
        }

    }
}

void generateRandomChromosomes(set_type set, chromo_type *chromo) {
    for(int i=0; i < chromoLength; i++){
        chromo -> genes[i] = (rand() > (RAND_MAX / 2) );
    }
}

// Assignment 3 b : Perform a cross-over mutation between two chromosomes

void chromosomeCrossOver(set_type set, chromo_type *chromo1, chromo_type *chromo2) {

    // Use the given random method to determine the location where the chromosomes should be "cut"

    int crossOverGene = randomInt(0, chromoLength);

    chromo_type tempChrom;

    for (int i = crossOverGene; i < chromoLength; ++i) {
        tempChrom.genes[i] = chromo1->genes[i];
        chromo1->genes[i] = chromo2->genes[i];
        chromo2->genes[i] = tempChrom.genes[i];
    }
    // temp is temporary storage

    // Check for fitness
    chromo1->fitness = fitnessMeasuring(set, *chromo1);
    chromo2->fitness = fitnessMeasuring(set, *chromo2);
}

// Assignment 4

//For this exercise.....(Give explanation)

int heightOfTower(set_type set, bool selectedSet, chromo_type chromo) {
    int height = 0;
    int i = 0;
    for (i; i < chromoLength; i++) {
        if (chromo.genes[1] == selectedSet) {
            height += set[i];
        }
    }
    return height;
}


int towerHeightDifference(set_type set, chromo_type chromo){
    return abs((heightOfTower(set, true, chromo) - heightOfTower(set, false, chromo)));
}