#include <stdio.h>
#include "../matrix/matrix.h"
#include "../algorithms/algorithms.h"
#include "../vector/vector.h"
#include "../polynomial/polynomial.h"
#include "../athlete/athlete.h"
#include "../product/product.h"
#include "../order/order.h"

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

void eighthTask(char *fileName, matrix *ms, int nMatrices){
    wMatrixToBinFile(fileName, ms, nMatrices);

    matrix* msResult = rMatrixFromBinFile(fileName);
    for (size_t matrixInd = 0; matrixInd < nMatrices; matrixInd++){
        if (!isSymmetricMatrix(&msResult[matrixInd])){
            transposeSquareMatrix(&msResult[matrixInd]);
        }
    }

    wMatrixToBinFile(fileName, msResult, nMatrices);
}


void ninthTask(char *fileName, athlete *arrayAthletes, int countAthletes,
               int needAthletes, athlete *rArrayAthletes,
               athlete **rightAthletes){
    if (countAthletes < needAthletes){
        printf("Требуемое количество атлетов превышает их количество");
        exit(1);
    }

    wAthletesToBinFile(fileName, arrayAthletes, countAthletes);

    int rCountAthletes;
    rArrayAthletes = rAthletesFromBinFile(fileName, &rCountAthletes);

    quickSortAthletes(rArrayAthletes, 0, rCountAthletes - 1);

    int countSkipAthletes = rCountAthletes - needAthletes;
    *rightAthletes = rArrayAthletes + countSkipAthletes;

    wAthletesToBinFile(fileName, *rightAthletes, needAthletes);
}


void tenthTask(char *fileNameProducts, char *fileNameOrders,
               product *arrayProducts, size_t countProducts,
               order *arrayOrders, size_t countOrders,
               product **rArrayProductsIndicator){
    wProductsToBinFile(fileNameProducts, arrayProducts, countProducts);
    wOrdersToBinFile(fileNameOrders, arrayOrders, countOrders);

    size_t rCountProducts;
    size_t countZeroProducts = 0;
    product *rArrayProducts = rProductsFromBinFile(fileNameProducts,
                                                   &rCountProducts);

    size_t rCountOrders;
    order *rArrayOrders = rOrdersFromBinFile(fileNameOrders, &rCountOrders);

    for (int indOrder = 0; indOrder < rCountOrders; indOrder++){
        size_t indProduct = searchIndProductFromArray(
                rArrayOrders[indOrder].productName, rArrayProducts,
                rCountProducts);

        rArrayProducts[indProduct].count -= rArrayOrders[indOrder].count;
        rArrayProducts[indProduct].allPrice -= rArrayOrders[indOrder].count *
                                               rArrayProducts[indProduct].pricePerUnit;

        if (rArrayProducts[indProduct].count == 0){
            countZeroProducts++;
        }
    }

    *rArrayProductsIndicator = rArrayProducts;
    wNonZeroProductsToBinFile(fileNameProducts, rArrayProducts, countProducts,
                              countZeroProducts);
}