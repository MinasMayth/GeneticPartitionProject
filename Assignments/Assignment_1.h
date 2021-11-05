//
// Created by samya on 02/11/2021.
//

#ifndef GENETICPARTITION_ASSIGNMENT_1_H
#define GENETICPARTITION_ASSIGNMENT_1_H

#include <stdbool.h>

#define INT_MAX 2147483647

#define numBlocks 20
// number of blocks in the input set
#define chromLength numBlocks
//length of chromosome
#define popSize 10
//number of chromosomes in population
int blocks[numBlocks];
// Maximum value when automatically generating
#define AUTO_MAX (INT_MAX / 20)

//Defining the types
typedef int set_t[numBlocks];

typedef bool gene_t;

typedef struct {
    gene_t genes[chromLength];
    int fitness;
} chromo_t;

//Functions used sorted by assignment question :
//Functions used in the first question
void readInitialDataset(set_t set, bool automatic);

//Functions used in the second question
void generateRandomChromosomes(set_t set,chromo_t *chromo);

//Functions used in the third question
//Mutation function
void mutateChromo(set_t, chromo_t *chromo);

//Fitness Measurement function --> Still needs to be written !! Example at line 311 Page 21
int fitnessMeasuring(set_t set, chromo_t chromo);

//Cross Over function
void chromosomeCrossOver(set_t, chromo_t *chromo1, chromo_t *chromo2);

//Random Function --> Still needs to be written !!! Example is in the assigment paper
int randomInt(int lower,int upper);

//Functions used in the fourth question
//Function to calculate the size of the towers
int heightOfTower(set_t set, bool selectedSet,chromo_t chromo);



bool generation[popSize][chromLength];





#endif //GENETICPARTITION_ASSIGNMENT_1_H
