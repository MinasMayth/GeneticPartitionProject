//
// Created by samya on 02/11/2021.
//

#ifndef GENETICPARTITION_ASSIGNMENT_1_H
#define GENETICPARTITION_ASSIGNMENT_1_H

#include <stdbool.h>

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

//Defining the types
typedef int set_type[numBlocks];

typedef bool gene_type;

typedef struct {
    gene_type genes[chromoLength];
    int fitness;
} chromo_type;

//Functions used sorted by assignment question :
//Functions used in the first question
void generateInitialTowerSet(set_type set, bool automatic);

//Functions used in the second question
void generateRandomChromosomes(set_type set, chromo_type *chromo);

//Functions used in the third question
//Mutation function
void mutateChromo(set_type, chromo_type *chromo);

//Fitness Measurement function --> Still needs to be written !! Example at line 311 Page 21
int fitnessMeasuring(set_type set, chromo_type chromo);

//Cross Over function
void chromosomeCrossOver(set_type, chromo_type *chromo1, chromo_type *chromo2);

//Functions used in the fourth question
//Function to calculate the size of the towers
int heightOfTower(set_type set, bool selectedSet, chromo_type chromo);



bool generation[popSize][chromoLength];

#endif //GENETICPARTITION_ASSIGNMENT_1_H
