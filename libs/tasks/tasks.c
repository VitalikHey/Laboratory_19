#include <stdio.h>
#include "../matrix/matrix.h"
#include "../algorithms/algorithms.h"

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
