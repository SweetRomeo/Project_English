//
// Created by BERKE on 11.05.2023.
//

#ifndef UNTITLED2_TAKTIK_H
#define UNTITLED2_TAKTIK_H
#include "Koloni.h"

struct FIGHT{
    int (*Savas)();
};

typedef struct FIGHT* Fight;

int setSavas(Fight this);
void createColonyTest(struct COLONY**,const int *num_data_res);
int Savas();



#endif //UNTITLED2_TAKTIK_H
