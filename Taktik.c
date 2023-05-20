//
// Created by BERKE on 11.05.2023.
//

#include <stdlib.h>
#include <stdio.h>
#include "Taktik.h"

int setSavas(Fight this)
{
    this->Savas = &Savas;
    return this->Savas();
}


void createColonyTest(struct COLONY** this,const int *num_data_res)
{
    static int i = 0;
    char symbol[] = {'%', '@', '*', '?','^', '#', '$', '&'};
    *this = createColony(symbol[i], num_data_res[i], num_data_res[i] * num_data_res[i], 0, 0, 0);
    ++i;
}

int Savas()
{
    return rand() % 1000;
}

