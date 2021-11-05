//
// Created by Alexander Vogt on 04/11/2021.
//

#include "Assignment_4.h"
// Assignment 4

//For this exercise.....(Give explanation)

int heightOfTower(set_type set, bool selectedSet, chromo_type chromo){
    int height = 0;
    int i = 0;
    for(i; i < chromoLength; i++){
        if (chromo.genes[1]== selectedSet){
            height += set[i];
        }
    }
    return height;
}



