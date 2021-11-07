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

#define NUMBER_OF_BlOCKS 20
// number of blocks in the input set
#define LENGTH_OF_CHROMOSOME NUMBER_OF_BlOCKS
//length of chromosome
#define POPULATION_SIZE 10
//number of chromosomes in population
int blocks[NUMBER_OF_BlOCKS];
// Maximum value when automatically generating
#define AUTO_MAX (INT_MAX / 20)

//Fitness constant
#define WORST_FITNESS INT_MAX

// Indexing best and worst chromosomes

#define WORST_CHROMOSOME (POPULATION_SIZE-1)
#define BEST_CHROMOSOME 0

// Convergence status

#define CONVERGENCE 0
#define SOLUTION 1
#define NO_IMPROVEMENTS -1
#define AFTER_MAX_ITER -2




// Types

typedef int set_type[NUMBER_OF_BlOCKS];
typedef bool gene_type;
typedef struct {
    gene_type genes[LENGTH_OF_CHROMOSOME];
    int fitness;
} chromo_type;

//Main Program Functions
void initialiseGeneration(set_type set, chromo_type *generation);
void performNaturalSelection(chromo_type *generation);
int checkForConvergence(chromo_type *generation, chromo_type *solutionChromosome, int *noChangeIterations,
                        int lastBestFitness);
int simulateEvolution(set_type set, int *solutionDiff);


void generateInitialTowerSet(set_type set, bool automatic);

//Functions related to calculating fitness of a chromosome
int heightOfTower(const set_type set, bool selectedSet, chromo_type chromo);
int towerHeightDifference(const set_type set, chromo_type chromo);

//Chromosome Functions
//Functions used in the second question
void generateRandomChromosomes(set_type set, chromo_type *chromo);
//Functions used in the third question
//Mutation function
void mutateChromosome(set_type set, chromo_type *chromo);
//Cross Over function
void chromosomeCrossOver(set_type set, chromo_type *chromo1, chromo_type *chromo2);
//sorting, copying and replacing
void sortChromosomes(chromo_type *generation);
void copyChromosome(chromo_type *to_overwrite, chromo_type to_copy);
void replaceChromosomes(
        const int *strongChromosomes,
        int *weakChromosomes,
        chromo_type *generation,
        int amountReplaced
);

//Permute two chromosomes in the generation
void permute(int i, int j, chromo_type *generation);


//Utility Functions
//Random Function --> Still needs to be written !!! Example is in the assigment paper
int randomInt(int lower,int upper);




// Functions

//After initialisation, the main process now looks like this:
//1. Make a new generation.
//2. Perform selection.
//3. Check for convergence (e.g. do we have a perfect solution).
//4. If not, back to the first step, else print result.

#endif