#ifndef LABORATORY_19_TASKS_H
#define LABORATORY_19_TASKS_H

#include "../matrix/matrix.h"

void firstTask(char *fileName, matrix *ms, int nMatrices);

double* secondTask(char *fileName, double arrayNums[],
                   size_t lengthArray, size_t *newArraySize);

void thirdTask(char *fileName, char expression[], double *result);

void fourthTask(char *fileName, char *s, char *desiredSequence,
                size_t sizeSequence, char *result);

void fifthTask(char *fileName, char *s, char *result);

#endif //LABORATORY_19_TASKS_H
