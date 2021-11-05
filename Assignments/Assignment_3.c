//
// Created by Alexander Vogt on 03/11/2021.
//
#include<stdlib.h>
#include "Assignment_2.h"
#include "Assignment_1.h"
#include "Assignment_3.h"

// Assignment 3 a: Mutate a single gene in a chromosome.

void mutateChromo(set_t set, chromo_t *chromo) {
    int mutatedGene = randomInt(0, chromLength);

    chromo->genes[mutatedGene] = (chromo->genes[mutatedGene] + 1) % 2;
    chromo->fitness = fitnessMeasuring(set, *chromo);
}
 // Assignment 3 b : Perform a cross-over mutation between two chromosomes

 void chromosomeCrossOver(set_t set, chromo_t *chromo1, chromo_t *chromo2) {

     // Use the given random method to determine the location where the chromosomes should be "cut"

     int crossOverGene = randomInt(0, chromLength);

     chromo_t tempChrom;

     for (int i = crossOverGene; i < chromLength; ++i) {
         tempChrom.genes[i] = chromo1->genes[i];
         chromo1->genes[i] = chromo2->genes[i];
         chromo2->genes[i] = tempChrom.genes[i];
 }
     // temp is temporary storage

     // Check for fitness
     chromo1->fitness = fitnessMeasuring(set, *chromo1);
     chromo2->fitness = fitnessMeasuring(set, *chromo2);
 }

