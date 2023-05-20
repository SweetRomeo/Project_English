#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "Oyun.h"
#include "Taktik.h"
#include "Koloni.h"
#include "Uretim.h"

#define randomize() srand(time(NULL))
#define SIZE 100

void readInputBuffer(char* str, char ch, int* stringSize, int* spaceCount, int* lastSpaceFlag)
{
    while ((ch = getchar()) != '\n' && (*stringSize < SIZE - 1)) {
        str[*stringSize] = ch;
        if (ch == '\b') {
            printf("\b \b");
            --*stringSize;
            if (*lastSpaceFlag)
                --*spaceCount;
        } else {
            ++*stringSize;
            printf("%c", ch);
            if (ch == ' ') {
                ++*spaceCount;
                *lastSpaceFlag = 1;
            } else {
                *lastSpaceFlag = 0;
            }
        }
    }
}

int powerOfTen(int num)
{
    int res = 1;
    int i;
    for (i = 0; i < num; i++)
        res *= 10;
    return res;
}

int* unpackData(const char* stringData, int spaceCount)
{
    int temp = 0;
    int stringIndex = 0;
    int* numData = (int*)malloc(spaceCount * sizeof(int));
    int i;
    for (i = 0; i < spaceCount; i++)
        numData[i] = 0;
    spaceCount = 0;
    while (stringData[stringIndex] != '\0') {
        while (stringData[stringIndex] != ' ') {
            stringIndex++;
            temp++;
        }
        for (i = temp - 1; i >= 0; i--) {
            numData[spaceCount] += powerOfTen(i) * (stringData[stringIndex - i - 1] - '0');
        }
        spaceCount++;
        stringIndex++;
        temp = 0;
    }
    return numData;
}

int main()
{
    char str[SIZE];
    char ch = 0;
    int stringSize = 0;
    int spaceCount = 0, lastSpaceFlag = 0;
    readInputBuffer(str, ch, &stringSize, &spaceCount, &lastSpaceFlag);
    str[stringSize] = ' ';
    str[stringSize + 1] = '\0';
    printf("\n");
    printf("Input string: %s\n", str);
    printf("Number of spaces: %d\n", spaceCount);
    int numberOfColonies = ++spaceCount;
    Colony* colonies = (Colony*)malloc(sizeof(Colony) * numberOfColonies);
    int* numDataRes = unpackData(str, numberOfColonies);
    for (int i = 0; i < numberOfColonies; ++i)
        createColonyTest(&colonies[i], numDataRes);
    int deathCount = 0;
    int turnCount = 1;
    while (1) {
        printf("----------------------------------------------------------------------------\n");
        printf("Turn Count: %d\n", turnCount);
        printf("Colony    Population   Food Stock     Wins       Losses\n");
        turnCount++;
        for (int i = 0; i < spaceCount; i++) {
            if (!colonies[i]->isDead && (colonies[i]->population <= 0 || colonies[i]->foodStock <= 0)) {
                deathCount++;
                colonies[i]->isDead = 1;
                printf("%d died.\n", i);
            }
            if (!colonies[i]->isDead)
                printf("%4c %8d %13d %13d %13d\n", colonies[i]->symbol, colonies[i]->population, colonies[i]->foodStock, colonies[i]->wins, colonies[i]->losses);
            else
                printf("%4c      --         --         --        --\n", colonies[i]->symbol);
        }
        printf("----------------------------------------------------------------------------\n");

        for (int i = 0; i < spaceCount - 1; i++) {
            for (int j = i + 1; j < spaceCount; j++) {
                if (!(colonies[i]->isDead || colonies[j]->isDead)) {
                    int tempBattle1 = Savas(); // Colony i
                    int tempBattle2 = Savas(); // Colony j
                    int winner;
                    int foodTransferTemp;

                    if (tempBattle1 == tempBattle2) {
                        if (colonies[i]->population == colonies[j]->population)
                            winner = rand() % 2 + 1;
                        else if (colonies[i]->population > colonies[j]->population)
                            winner = 1;
                        else
                            winner = 2;
                    } else if (tempBattle1 > tempBattle2) {
                        winner = 1;
                    } else {
                        winner = 2;
                    }

                    if (winner == 1) {
                        colonies[i]->wins++;
                        colonies[j]->losses++;
                        colonies[j]->population -= colonies[j]->population * ((int)((double)(tempBattle1 - tempBattle2) / 1000));
                        foodTransferTemp = (int)(((double)colonies[j]->foodStock / 100) * 10);
                        colonies[i]->foodStock += foodTransferTemp;
                        colonies[j]->foodStock -= foodTransferTemp;
                    } else {
                        colonies[i]->losses++;
                        colonies[j]->wins++;
                        colonies[i]->population -= colonies[i]->population * ((int)((double)(tempBattle2 - tempBattle1) / 1000));
                        foodTransferTemp = (int)(((double)colonies[i]->foodStock / 100) * 10);
                        colonies[j]->foodStock += foodTransferTemp;
                        colonies[i]->foodStock -= foodTransferTemp;
                    }
                }
            }
        }

        for (int i = 0; i < spaceCount; i++) {
            colonies[i]->population += (int)(((double)colonies[i]->population / 100) * 20);
            colonies[i]->foodStock -= colonies[i]->population * 2;
        }

        if (deathCount >= spaceCount - 1)
            break;

        printf("Press any key to continue the battle...\n");
        while (!getchar())
            ;

    }

    free(colonies);
    return 0;
}