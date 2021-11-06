//
// Created by samya on 02/11/2021.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Assignment_1.h"

void generateInitialTowerSet(set_type set, bool automatic){
    if(automatic){
        for(int i=0; i < popSize; i++){
            set[i] = rand() % AUTO_MAX;
        }

        printf("Initial set generated: \n");
        for(int i = 0; i < popSize; i++) {
            printf("%d ", set[i]);
            printf("\n");
        }

    }else{
        int spaceLeft = INT_MAX;
        for(int i=0; i < numBlocks; i++) {
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