/* file        : GeneticPartitionCore.h
 * authors     : Samy Hashim (s.t.a.hashim@student.rug.nl)
 *             : Alexander Vogt (a.n.vogt@student.rug.nl)
 * date        : Due 05/11/2021
*/

// Constant and headers for the partition problem
#ifndef GENETICPARTITION_GENETICPARTITIONCORE_H
#define GENETICPARTITION_GENETICPARTITIONCORE_H

// Libraries

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

// Maximum value of an integer
#define INT_MAX 2147483647

#define numBlocks 20
// number of blocks in the input set
#define chromoLength numBlocks
//length of chromosome
#define popSize 10
//number of chromosomes in population
int blocks[numBlocks];
// Maximum value when automatically generating
#define AUTO_MAX (INT_MAX / 20)
// Types

typedef int set_type[numBlocks];
typedef bool gene_type;
typedef struct {
    gene_type genes[chromoLength];
    int fitness;
} chromo_type;

//Main Program Functions
int createNewGeneration(set_type set, chromo_type *generation);
void performNaturalSelection(set_type set, chromo_type *generation);
void checkForConvergence(set_type set, chromo_type *generation, chromo_type *solutionChromosome,
                         int *noChangeIterations, int lastBestFitness);
void simulateEvolution(set_type set, int *solutionDiff);


void readInitialDataset(set_type set, bool automatic);

//Functions related to calculating fitness of a chromosome
int heightOfTower(set_type set, bool selectedSet, chromo_type chromo);
towerHeightDifference(set_type set, chromo_type chromo);

//Chromosome Functions
//Functions used in the second question
void generateRandomChromosomes(set_type set, chromo_type *chromo);
//Functions used in the third question
//Mutation function
void mutateChromosome(set_type, chromo_type *chromo);
//Cross Over function
void chromosomeCrossOver(set_type, chromo_type *chromo1, chromo_type *chromo2);
//sorting, copying and replacing
void sortChromosomes(chromo_type *generation);
void copyChromosome(chromo_type *to_overwrite, chromo_type to_copy);
void replaceChromosomes(
        int *strongChromosomes,
        int *weakChromosomes,
        chromo_type *generation,
        int amountReplaced
        );


//Utility Functions
//Random Function --> Still needs to be written !!! Example is in the assigment paper
int randomInt(int lower,int upper);




// Functions

//After initialisation, the main process now looks like this:
//1. Make a new generation.
//2. Perform selection.
//3. Check for convergence (e.g. do we have a perfect solution).
//4. If not, back to the first step, else print result.






#endif //GENETICPARTITION_GENETICPARTITIONCORE_H
