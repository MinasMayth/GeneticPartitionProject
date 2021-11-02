//
// Created by samya on 02/11/2021.
//

#ifndef GENETICPARTITION_ASSIGNMENT_1_H
#define GENETICPARTITION_ASSIGNMENT_1_H

#include <stdbool.h>

#define numBlocks 20
// number of blocks in the input set
#define chromLength numBlocks
//length of chromosome
#define popSize 10
//number of chromosomes in population
int blocks[numBlocks];
// Maximum value when automatically generating
#define AUTO_MAX (INT_MAX / 20)

typedef int set_t[numBlocks];

bool generation[popSize][chromLength];

void readInitialDataset(set_t set, bool automatic);



#endif //GENETICPARTITION_ASSIGNMENT_1_H
