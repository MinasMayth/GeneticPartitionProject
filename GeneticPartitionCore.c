/* file        : GeneticPartitionCore.c
 * authors     : Samy Hashim (s.t.a.hashim@student.rug.nl)
 *             : Alexander Vogt (a.n.vogt@student.rug.nl)
 * date        : Due 07/11/2021
*/
#include "GeneticPartitionCore.h"
#include "stdbool.h"
#include "GeneticPartitionConfigurationSimulation.h"
#include "Testing.h"
#include "GeneticPartitionVisualization.h"

/*
 * Methods used for the partition problem
 */

void generateInitialTowerSet(set_type set, bool automatic){
    if(automatic){
        for(int i=0; i < POPULATION_SIZE; i++){
            set[i] = rand() % AUTO_MAX;
        }
        printf("Initial set generated: \n");
        for(int i = 0; i < POPULATION_SIZE; i++) {
            printf("%d ", set[i]);
            printf("\n");
        }

    }else{
        int spaceLeft = INT_MAX;
        for(int i=0; i < NUMBER_OF_BlOCKS; i++) {
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

//Assignment 7


// Function that creates the initial generation
void createNewGeneration(set_type set, chromo_type *generation){
    int x = 0;
    for (x; x < POPULATION_SIZE; x++){
        generateRandomChromosomes(set, &generation[x]);
    }
}

// Function that sorts the chromosomes in an array with the fittest at index 0

void sortChromosomes(chromo_type *generation){
    for (int i = 0; i<POPULATION_SIZE;i++){
        int minimum = i;

        for (int j = 0; j<POPULATION_SIZE;j++){
            if (generation[j].fitness < generation[minimum].fitness) {
                minimum = j;
            }
        }
        permute(i,minimum,generation);
    }
}



void permute(int i, int j, chromo_type *generation) {
    chromo_type temporaryChromosome;

    copyChromosome(&temporaryChromosome,generation[i]);
    copyChromosome(generation+i, generation[j]);
    copyChromosome(generation+j,temporaryChromosome);
}

// Copy Chromosomes function

void copyChromosome (chromo_type *to_overwrite, chromo_type to_copy){
    for (int x = 0; x < LENGTH_OF_CHROMOSOME; x++) {
        to_overwrite -> genes[x] = to_copy.genes[x];
    }
    to_overwrite -> fitness = to_copy.fitness;

}

// Replace two chromosome by index

void replaceChromosomes(int *strongChromosome,int *weakChromosome,chromo_type *generation,int numberOfReplacedChromosomes){

    for (int i = 0; i < numberOfReplacedChromosomes; i++){
        copyChromosome(generation + weakChromosome[i],generation[strongChromosome[i]]);
    }
}




/*
 * This functions performs the selection by replacing the 3 weakest by the 3 'fittest' chromosomes
 */

void performNaturalSelection(set_type set, chromo_type *generation){

    int strongChromosomes[simulationConfiguration.numberOfReplacedChromosomes];
    int weakChromosomes[simulationConfiguration.numberOfReplacedChromosomes];

 /*
  * Sorting the generation along fitness
  */

    for (int i=0;i<simulationConfiguration.numberOfReplacedChromosomes;i++) {

        weakChromosomes[i] = WORST_CHROMOSOME - i ;
        strongChromosomes[i] = i;
    }

    replaceChromosomes(              //Still needs to be written
        weakChromosomes,
        strongChromosomes,
        generation,
        simulationConfiguration.numberOfReplacedChromosomes
        );

    //Sort Population

    sortChromosomes(generation);
}

//Check for solution

int checkForConvergence(set_type set, chromo_type *generation, chromo_type *solutionChromosome,
                         int *noChangeIterations, int lastBestFitness){

    //Check if the best chromosomes is equal to the first chromosome

    if (generation[BEST_CHROMOSOME].fitness < lastBestFitness ) {

        *noChangeIterations = 0;
    } else {
            (*noChangeIterations)++;
}
    if (generation[BEST_CHROMOSOME].fitness == 0) {
        copyChromosome(solutionChromosome,generation[BEST_CHROMOSOME]);
        return SOLUTION;

    } else if (*noChangeIterations > simulationConfiguration.iterations) {
        copyChromosome(solutionChromosome, generation[BEST_CHROMOSOME]);
        return NO_IMPROVEMENTS;

    }

    // If no solution
    return CONVERGENCE;

}

void newGeneration(set_type set,chromo_type *generation) {
    //Cross-over (Except the fittest chromosome hence RandInt(1,POPULATION_SIZE))
    for(int i = 0; i < simulationConfiguration.numberOfCrossOvers; i++){

        int mutatedChromsome1,mutatedChromsome2;

        mutatedChromsome1 = randomInt(1,POPULATION_SIZE);
        mutatedChromsome2 = randomInt(1,POPULATION_SIZE);

        chromosomeCrossOver(set,&generation[mutatedChromsome1],&generation[mutatedChromsome2]);

    }
    //Mutation
    for (int i = 0;i<simulationConfiguration.numberOfMutations;i++){

        int mutatedChromosome = randomInt(1,POPULATION_SIZE);

        mutateChromosome(set,&generation[mutatedChromosome]);
    }
    //Sort By Fitness

    sortChromosomes(generation);
}


        void generateRandomChromosomes(set_type set, chromo_type *chromo) {
    for(int i=0; i < LENGTH_OF_CHROMOSOME; i++){
        chromo -> genes[i] = (rand() > (RAND_MAX / 2) );
    }
}

// Assignment 3 b : Perform a cross-over mutation between two chromosomes

void chromosomeCrossOver(set_type set, chromo_type *chromo1, chromo_type *chromo2) {

    // Use the given random method to determine the location where the chromosomes should be "cut"

    int crossOverGene = randomInt(0, LENGTH_OF_CHROMOSOME);

    chromo_type tempChrom;

    for (int i = crossOverGene; i < LENGTH_OF_CHROMOSOME; ++i) {
        tempChrom.genes[i] = chromo1->genes[i];
        chromo1->genes[i] = chromo2->genes[i];
        chromo2->genes[i] = tempChrom.genes[i];
    }
    // temp is temporary storage

    // Check for fitness
    chromo1->fitness = towerHeightDifference(set, *chromo1);
    chromo2->fitness = towerHeightDifference(set, *chromo2);
}

// Assignment 4

//For this exercise.....(Give explanation)

int heightOfTower(set_type set, bool selectedSet, chromo_type chromo) {
    int height = 0;
    int i = 0;
    for (i; i < LENGTH_OF_CHROMOSOME; i++) {
        if (chromo.genes[1] == selectedSet) {
            height += set[i];
        }
    }
    return height;
}


int towerHeightDifference(set_type set, chromo_type chromo){
    return abs((heightOfTower(set, true, chromo) - heightOfTower(set, false, chromo)));
}

int randomInt(int lower, int upper) {
    int r;
    const unsigned int range = 1 + upper - lower;
    const unsigned int buckets = RAND_MAX/range;
    const unsigned int limit = buckets/range;
    /* Create equal size buckets all in a row, then fire randomly towards
    * the buckets until you land in one of them. All buckets are equally
    * likely. If you land off the end of the line of buckets, try again. */

    do
    {
        r = rand();
    } while (r >= limit);
    return lower + (r/buckets);
}
int simulateEvolution(int *set, int *solutionDiff) {

    chromo_type solutionChromosome;
    chromo_type generation[POPULATION_SIZE];

    createNewGeneration(set, generation);
    chromosomeCrossOver(set, generation, generation+1);


    int totalIterations = 0;
    int iterationsNoImprovement = 0;
    int simulationStatus = CONVERGENCE;
    int lastBestFitness = WORST_FITNESS;

    while (simulationStatus == CONVERGENCE){
        totalIterations++;
        performNaturalSelection(set, generation);
        simulationStatus = checkForConvergence(
                set, generation, &solutionChromosome,
                &iterationsNoImprovement, lastBestFitness
        );

        if(totalIterations > MAX_ITERATION){
            simulationStatus = AFTER_MAX_ITER;
        }
        if(simulationStatus != CONVERGENCE){
            printOutput(set, simulationStatus, solutionChromosome);
            *solutionDiff = towerHeightDifference(set, solutionChromosome);
            return totalIterations;
        }else {
            lastBestFitness = generation[BEST_CHROMOSOME].fitness;
            createNewGeneration(set, generation);
        }

    }

    return totalIterations;
}

void mutateChromosome(set_type set, chromo_type *chromo) {
    int geneToMutate = randomInt(0, LENGTH_OF_CHROMOSOME);

    chromo->genes[geneToMutate] = (chromo->genes[geneToMutate] + 1) % 2;
    chromo->fitness = towerHeightDifference(set, *chromo);

}
