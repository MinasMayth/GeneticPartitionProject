/* file        : GeneticPartitionCore.c
 * authors     : Samy Hashim (s.t.a.hashim@student.rug.nl)
 *             : Alexander Vogt (a.n.vogt@student.rug.nl)
 * date        : Due 07/11/2021
*/
#include "GeneticPartitionCore.h"
#include "stdbool.h"
#include "GeneticPartitionConfigurationSettings.h"
#include "GeneticPartitionVisualization.h"

/*
 * Methods used for the partition problem
 */

// ASSIGNMENT 1: Write a function that reads the heights of the blocks
void generateInitialTowerSet(set_type set, bool automatic){
    if(automatic){
        for(int i=0; i < NUMBER_OF_BlOCKS; i++){
            set[i] = randomInt(0, AUTO_MAX);
        }
    }else{
        printf("Please enter 20 positive integers:\n");
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
void initialiseGeneration(set_type set, chromo_type *generation){
    for (int x = 0; x < POPULATION_SIZE; x++){
        generateRandomChromosomes(set, &generation[x]);
    }
}

// Function that sorts the chromosomes in an array with the fittest at index 0

void sortChromosomes(chromo_type *generation){
    for (int i = 0; i<POPULATION_SIZE;i++){
        int minimum = i;
        for (int j = i; j<POPULATION_SIZE;j++){
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

void replaceChromosomes(const int *strongChromosome,int *weakChromosome,chromo_type *generation,int numberOfReplacedChromosomes){
    for (int x = 0; x < numberOfReplacedChromosomes; x++){
        copyChromosome(generation + weakChromosome[x], generation[strongChromosome[x]]);
    }
}


/*
 * This functions performs the selection by replacing the 3 weakest by the 3 'fittest' chromosomes
 */

void performNaturalSelection(chromo_type *generation) {
    int strongChromosomes[simulationSettings.numberOfReplacedChromosomes];
    int weakChromosomes[simulationSettings.numberOfReplacedChromosomes];

 /*
  * Sorting the generation along fitness
  */
    for (int x=0; x < simulationSettings.numberOfReplacedChromosomes; x++) {
        weakChromosomes[x] = WORST_CHROMOSOME - x ;
        strongChromosomes[x] = x;
    }
    replaceChromosomes(
        weakChromosomes,
        strongChromosomes,
        generation,
        simulationSettings.numberOfReplacedChromosomes
        );

    //Sort Population

    sortChromosomes(generation);
}

//Check for solution

int checkForConvergence(chromo_type *generation, chromo_type *solutionChromosome, int *noChangeIterations,
                        int lastBestFitness) {

    //Check if the best chromosomes is equal to the first chromosome
    if (generation[BEST_CHROMOSOME].fitness < lastBestFitness ) {
        *noChangeIterations = 0;
        copyChromosome(solutionChromosome,generation[BEST_CHROMOSOME]);
    } else {
            (*noChangeIterations)++;
}
    if (generation[BEST_CHROMOSOME].fitness == 0) {
        copyChromosome(solutionChromosome,generation[BEST_CHROMOSOME]);
        return SOLUTION;

    } else if (*noChangeIterations > simulationSettings.iterations) {
        copyChromosome(solutionChromosome, generation[BEST_CHROMOSOME]);
        return NO_IMPROVEMENTS;

    }

    // If no solution
    return CONVERGENCE;

}

void newGeneration(set_type set,chromo_type *generation) {
    //Cross-over (Except the fittest chromosome hence RandInt(1,POPULATION_SIZE))
    for(int i = 0; i < simulationSettings.numberOfCrossOvers; i++){

        int mutatedChromsome1,mutatedChromsome2;

        mutatedChromsome1 = randomInt(1,POPULATION_SIZE);
        mutatedChromsome2 = randomInt(1,POPULATION_SIZE);

        chromosomeCrossOver(set,&generation[mutatedChromsome1],&generation[mutatedChromsome2]);

    }
    //Mutation
    for (int i = 0; i < simulationSettings.numberOfMutations; i++){

        int mutatedChromosome = randomInt(1,POPULATION_SIZE);

        mutateChromosome(set,&generation[mutatedChromosome]);
    }
    //Sort By Fitness

    sortChromosomes(generation);
}

//ASSIGNMENT 2: Write a function that fills a chromosome with random boolean values.
void generateRandomChromosomes(set_type set, chromo_type *chromo) {
    for(int i=0; i < LENGTH_OF_CHROMOSOME; i++){
        chromo -> genes[i] = randomInt(0,2);
    }
    chromo -> fitness = 0;
    chromo -> fitness = towerHeightDifference(set, *chromo);
}

// Assignment 3 b : Perform a cross-over mutation between two chromosomes
void chromosomeCrossOver(set_type set, chromo_type *chromo1, chromo_type *chromo2) {

    // Use the given random method to determine the location where the chromosomes should be "cut"

    int crossOverGene = randomInt(0, LENGTH_OF_CHROMOSOME);

    chromo_type tempChrom;

    for (int i = crossOverGene; i < LENGTH_OF_CHROMOSOME; i++) {
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

//For this exercise we sum all individual block height values to find the total

int heightOfTower(const set_type set, bool selectedSet, chromo_type chromo) {
    int height = 0;
    for (int i=0; i < LENGTH_OF_CHROMOSOME; i++) {
        if (chromo.genes[i] == selectedSet) {
            height += set[i];
        }
    }
    return height;
}

//ASSIGNMENT 5: To implement “natural selection” we will need a measure of fitness. A natural choice is the difference
//in the height of the towers. Write a function to compute this difference, either using the function from
//the previous assignment, or develop a more efficient way to do it

//ON ASSIGNMENT 6: While it is possible to write a function that uses the inverse relationship between difference
//and fitness, so that fitness increases when we decrease difference, it isn't really necessary... There would be
//issues arising from the conversion of float numbers, and so it's just a lot easier to remember that fitness is
//better when it is closer to 0, and that stronger chromosomes will appear earlier in the generation
int towerHeightDifference(const set_type set, chromo_type chromosome){
    int diff=0;
    for(int x=0; x < LENGTH_OF_CHROMOSOME; x++){
        if (chromosome.genes[x]) {
            diff += -1 * (set[x]);
        } else {
            diff += 1 * (set[x]);
        }
    }
    return abs(diff); //absolute difference between both sets
    }

int randomInt(int lower, int upper) {
   int r = rand();
   int range = upper - lower;

   if(range < 10){
       for(int x=0; x<range; x++){
           if(r >= x*(RAND_MAX/range) && r < (x+1)*(RAND_MAX)/range){
               return (lower+x);
           }
       }
   }else{
       return (lower + (r%range));
   }
    return 1;
}
int simulateEvolution(int *set, int *solutionDiff) {

    chromo_type solutionChromosome;
    chromo_type generation[POPULATION_SIZE];

    initialiseGeneration(set, generation);
    chromosomeCrossOver(set, generation, generation+1);

    int totalIterations = 0;
    int iterationsNoImprovement = 0;
    int simulationStatus = CONVERGENCE;
    int lastBestFitness = WORST_FITNESS;

    while (simulationStatus == CONVERGENCE){
        totalIterations++;
        performNaturalSelection(generation);
        simulationStatus = checkForConvergence(generation, &solutionChromosome,
                                               &iterationsNoImprovement, lastBestFitness
        );
        if(totalIterations > MAX_T1){
            printf("\nMax iterations reached");
            simulationStatus = AFTER_MAX_ITER;
        }
        if(simulationStatus != CONVERGENCE){
            printOutput(set, simulationStatus, solutionChromosome);
            *solutionDiff = towerHeightDifference(set, solutionChromosome);
            return totalIterations;
        }else {
            lastBestFitness = generation[BEST_CHROMOSOME].fitness;
            newGeneration(set, generation);
        }

    }

    return totalIterations;
}

//ASSIGNMENT 3A: Write a function that mutates a random gene in a chromosome.
void mutateChromosome(set_type set, chromo_type *chromo) {
    int geneToMutate = randomInt(0, LENGTH_OF_CHROMOSOME);

    chromo->genes[geneToMutate] = (chromo->genes[geneToMutate] + 1) % 2;
    chromo->fitness = towerHeightDifference(set, *chromo);

}
