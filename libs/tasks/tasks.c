#include <stdio.h>
#include "../matrix/matrix.h"
#include "../algorithms/algorithms.h"
#include "../vector/vector.h"
#include "../polynomial/polynomial.h"

void firstTask(char *fileName, matrix *ms, int nMatrices){
    wArrayOfMatrix(fileName, ms, nMatrices);

    int rCountMatrices;
    matrix *rMatricesArray = rMatrixFromFile(fileName, &rCountMatrices);

    for (int indMatrix = 0; indMatrix < rCountMatrices; indMatrix++){
        transposeSquareMatrix(&rMatricesArray[indMatrix]);
    }

    wArrayOfMatrix(fileName, rMatricesArray, rCountMatrices);
}


double* secondTask(char *fileName, double arrayNums[],
                   size_t lengthArray, size_t *newArraySize){
    wNumsToFile(fileName, arrayNums, lengthArray);

    double *newArrayNums = (double*)malloc(*newArraySize * sizeof(double));
    rNumsFromFile(fileName, newArrayNums, newArraySize);

    return arrayNums;
}


void thirdTask(char *fileName, char expression[], double *result){
    wStringToFile(fileName, expression);
    calculateArithmeticExpression(fileName, result);

    char result_str[20];
    sprintf(result_str, " = %lf", *result);
    strcat(expression, result_str);
    wStringToFile(fileName, expression);
}

void fourthTask(char *fileName, char *s, char *desiredSequence,
                size_t sizeSequence, char *result){
    wStringToFile(fileName, s);

    rFilterWordsFromFile(fileName, result, desiredSequence, sizeSequence);

    wStringToFile(fileName, result);
}


void fifthTask(char *fileName, char *s, char *result){
    wStringToFile(fileName, s);

    getLongestWordsInLineFromFile(fileName, result);

    wStringToFile(fileName, result);
}


void sixthTask(char *fileName, int powers[], double factors[],
               int monAmounts[], int polAmount, int x, int *result){
    wPolyToFile(fileName, powers, factors, monAmounts, polAmount);

    polynomial *ps = rPolyFromFile(fileName);

    *result = sortedPoly(ps, x, polAmount);

    savePolyResult(fileName, ps, polAmount);
}

void seventhTask(char *fileName, int numsArray[], size_t sizeArray,
                 vector *positive, vector *negative){
    wNumsToBinFile(fileName, numsArray, sizeArray);

    rFilterAndWriteNumsFromBinFile(fileName, positive, negative);
}