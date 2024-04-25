#ifndef LABORATORY_19_TASKS_H
#define LABORATORY_19_TASKS_H

#include <stdio.h>
#include "../matrix/matrix.h"
#include "../vector/vector.h"

void firstTask(char *fileName, matrix *ms, int nMatrices);

double* secondTask(char *fileName, double arrayNums[],
                   size_t lengthArray, size_t *newArraySize);

void thirdTask(char *fileName, char expression[], double *result);

void fourthTask(char *fileName, char *s, char *desiredSequence,
                size_t sizeSequence, char *result);

void fifthTask(char *fileName, char *s, char *result);

void sixthTask(char *fileName, int powers[], double factors[],
               int monAmounts[], int polAmount, int x, int *result);

void seventhTask(char *fileName, int numsArray[], size_t sizeArray,
                 vector *positive, vector *negative);

#endif //LABORATORY_19_TASKS_H
