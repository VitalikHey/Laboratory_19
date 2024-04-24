#ifndef LABORATORY_19_ALGORITHMS_H
#define LABORATORY_19_ALGORITHMS_H

#include "../matrix/matrix.h"
#include <math.h>
#include <stdio.h>
#include <ctype.h>

// возвращает открытый файл или текст с ошибкой
FILE* openFile(char *fileName, char *action);

// заносит в файл fileName массив матриц ms
void wArrayOfMatrix(char *fileName, matrix *ms, int nMatrices);

// считывает из файла массив матриц и возвращает его
matrix* rMatrixFromFile(char *fileName, int *rCountMatrices);

// считывает вещественные числа из файла
void rNumsFromFile(char *fileName, double array[], size_t *sizeArray);

// записывает вещественные числа в файл
void wNumsToFile(char *fileName, double array[], size_t lengthArray);

// записывает значение арифметического выражения в файле
void calculateArithmeticExpression(char *fileName, double *result);

// записывает строку в файл
void wStringToFile(char *fileName, char *s);

// записывает в массив newS все слова из файла,
// которые содержат в себе заданную последовательность
void rFilterWordsFromFile(char *fileName, char *newS, char *desiredSequence,
                          size_t sizeSequence);

// записывает самое длинное слово из каждой строки файла в переменную result
void getLongestWordsInLineFromFile(char *fileName, char *result);

// записывает полиномы и их данные в файл
void wPolyToFile(char *fileName, int powers[], double factors[],
                 int monAmounts[], int polAmount);

// записывает в бинарный файл массив чисел
void wNumsToBinFile(char *fileName, int numsArray[], size_t sizeArray);

// записывает квадратные матрицу в файл
void wMatrixToBinFile(char *fileName, matrix *ms, int nMatrices);

// считывает и возвращает квадратные матрицы из файла
matrix* rMatrixFromBinFile(char *fileName);

#endif //LABORATORY_19_ALGORITHMS_H
