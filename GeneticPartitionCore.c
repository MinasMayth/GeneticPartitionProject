/* file        : GeneticPartitionCore.c
 * authors     : Samy Hashim (s.t.a.hashim@student.rug.nl)
 *             : Alexander Vogt (a.n.vogt@student.rug.nl)
 * date        : Due 07/11/2021
*/
#include "GeneticPartitionCore.h"
#include "stdbool.h"
#include "GeneticPartitionConfigurationSimulation.h"

/*
 * Methods used for the partition problem
 */

void readInitialDataset(set_type set, bool automatic){
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
    int i = 0;
    for (i;i< POPULATION_SIZE;i++){
        generateRandomChromosomes(set, &generation[i]);
    }
}

// Function that sorts the chromosomes in an array with the fittest at index 0

void sortChromosomes(chromo_type *generation){
    for (int x = 0; x<POPULATION_SIZE;x++){
        int minimum = x;

        for (int y = 0; y<POPULATION_SIZE;y++){
            if (generation[y].fitness < generation[minimum].fitness) {
                minimum = y;
            }
        }
        permute(x,minimum,generation);
    }
}

//Permute two chromosomes in the generation

void permute(int i, int j, chromo_type *generation){
    chromo_type temporaryChromosome;

    copyChromosome(&temporaryChromosome,generation[i]);
    copyChromosome(generation+i, generation[j]);
    copyChromosome(generation+j,temporaryChromosome);
}

// Copy Chromosomes function

void copyChromosome(chromo_type *toOverwrite, chromo_type toCopy){
    for (int x = 0;x < LENGTH_OF_CHROMOSOME;x++) {
        toOverwrite->genes[x] = toCopy.genes[x];
    }
    toOverwrite -> fitness = toCopy.fitness;
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

    for (int x=0;x<simulationConfiguration.numberOfReplacedChromosomes;x++) {

        weakChromosomes[x] = WORST_CHROMOSOME - x ;
        strongChromosomes[x] = x;
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

int convergence(
        set_type set,
        chromo_type *generation,
        chromo_type *SolutionChromosome,
        int *numberOfIterationsNoSolution,
        int previousBestFitness
        ) {

    //Check if the best chromosomes is equal to the first chromosome

    if (generation[BEST_CHROMOSOME].fitness < previousBestFitness ) {

        *numberOfIterationsNoSolution = 0;
    } else {
            (*numberOfIterationsNoSolution)++;
}
    if (generation[BEST_CHROMOSOME].fitness == 0) {
        copyChromosome(SolutionChromosome,generation[BEST_CHROMOSOME]);
        return SOLUTION;

    } else if (*numberOfIterationsNoSolution > simulationConfiguration.time) {
        copyChromosome(SolutionChromosome, generation[BEST_CHROMOSOME]);
        return NO_IMPROVEMENTS;

    }

    // If no solution
    return CONVERGENCE;

}

void newGeneration(set_type set,chromo_type *generation) {
    //Cross-over (Except the fittest chromosome hence RandInt(1,POPULATION_SIZE))
    for(int i = 0; i < simulationConfiguration.numberOfCrossOvers; i++){

        int mutatedChromosome1,mutatedChromosome2;

        mutatedChromosome1 = randomInt(1, POPULATION_SIZE);
        mutatedChromosome2 = randomInt(1, POPULATION_SIZE);

        chromosomeCrossOver(set, &generation[mutatedChromosome1], &generation[mutatedChromosome2]);

    }
    //Mutation
    for (int x = 0;x<simulationConfiguration.numberOfMutations;x++){

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
            simulationStatus = PREVIOUS_MAX_ITER;
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

int checkForConvergence(int *set, chromo_type *gen, chromo_type *solutionChromosome, int *noChangeIterations,
                        int lastBestFitness) {
    if(lastBestFitness > gen[BEST_CHROMOSOME].fitness){
        *noChangeIterations = 0;
    }else{
        (*noChangeIterations)++;
    }

    if(gen[BEST_CHROMOSOME].fitness == 0){
        copyChromosome(solutionChromosome, gen[BEST_CHROMOSOME]);
        return SOLUTION;
    }else if(*noChangeIterations > simulationConfiguration.time){
        copyChromosome(solutionChromosome, gen[BEST_CHROMOSOME]);
        return NO_IMPROVEMENTS;
    }
    return CONVERGENCE;
}
