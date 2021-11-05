
/* Description:
* Given two sets of positive integers, we create a pair of disjoint sets.
* The union of these two sets must be the original set, and the sum of the
* integers in each set must equal each other.
* We shall use a genetic algorithm to determine these two sets.
*
* Input: _Precisely_ SIZE_ORIGINAL_SET (20) integers, separated by whitespace
*
* Output: The solution chromosome, and how the chromosome leads to the best
* solution it comes to.
*/

#include <stdbool.h>
#include <stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include "Assignment_1.h"
#include "Assignment_2.h"
#include "Assignment_3.h"
#include "Assignment_4.h"
#include "Assignment_5.h"

#define numBlocks 20
// number of blocks in the input set
#define chromLength numBlocks
//length of chromosome
#define popSize 10
// Maximum value when automatically generating
#define AUTO_MAX (INT_MAX / 20)
typedef int set_t[numBlocks];

//number of chromosomes in population
set_t blocks;

bool generation[popSize][chromLength];


int main(){
    readInitialDataset(blocks, true);


    for(int i=0; i < chromLength; i++) {
        generateRandomChromosomes(blocks, (chromo_t *) &generation[i]);
    }
    return 0;
}