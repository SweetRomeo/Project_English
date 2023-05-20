//
// Created by BERKE on 11.05.2023.
//

#ifndef KOLONI_H
#define KOLONI_H

struct COLONY{
    char symbol;
    int population;
    int foodStock;
    int wins;
    int losses;
    int isDead;
    void (*destroy)(struct COLONY*);
};

typedef struct COLONY*Colony;

Colony createColony(char,int,int,int,int,int);
void destroyColony(Colony);



#endif //KOLONI_H
