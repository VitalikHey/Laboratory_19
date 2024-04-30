#ifndef INC_ALGORITHMS_H
#define INC_ALGORITHMS_H

#include "../matrix/matrix.h"
#include "../string/string.h"
#include "../polynomial/polynomial.h"
#include "../vector/vector.h"
#include "../athlete/athlete.h"
#include "../product/product.h"
#include "../order/order.h"

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

// возвращает 'истина', если слово содержит
// в себе искомую последовательность, иначе - 'ложь'
bool wordIncludesSequence(WordDescriptor word, char* sequence,
                          size_t sizeSequence);

// записывает в массив newS все слова из файла,
// которые содержат в себе заданную последовательность
void rFilterWordsFromFile(char *fileName, char *newS, char *desiredSequence,
                          size_t sizeSequence);

// записывает самое длинное слово из каждой строки файла в переменную result
void getLongestWordsInLineFromFile(char *fileName, char *result);

// записывает полиномы и их данные в файл
void wPolyToFile(char *fileName, int powers[], double factors[],
                 int monAmounts[], int polAmount);

// читает из файла полиномы и возвращает их
polynomial* rPolyFromFile(char *fileName);

// фильтрует полиномы, оставляя только нужные
int sortedPoly(polynomial* ps, int x, int polAmount);

// сохраняет результат фильтрации полиномов в файл
void savePolyResult(char *fileName, polynomial *ps, int polAmount);

// читает из бинарного файла список чисел, фильтрует их и записывает обратно
void rFilterAndWriteNumsFromBinFile(char *fileName,
                                    vector *positive, vector *negative);

// записывает в бинарный файл массив чисел
void wNumsToBinFile(char *fileName, int numsArray[], size_t sizeArray);

// записывает квадратные матрицу в файл
void wMatrixToBinFile(char *fileName, matrix *ms, int nMatrices);

// считывает и возвращает квадратные матрицы из файла
matrix* rMatrixFromBinFile(char *fileName);

// записывает структуры с информацией об атлетах в бинарный файл
void wAthletesToBinFile(char *fileName, athlete *arrayAthletes,
                        int countAthletes);

// считывает структуры с информацией об атлетах из бинарного файла
athlete* rAthletesFromBinFile(char *fileName, int *countAthletes);

// записывает в файл список структур товаров на складе
void wProductsToBinFile(char *fileName, product *arrayProducts,
                        size_t countProducts);

// записывает в файл список структур заказов
void wOrdersToBinFile(char *fileName, order *arrayOrders, size_t countOrders);

// читает из бинарного файла список товаров и возвращает их
product* rProductsFromBinFile(char *fileName, size_t *countProducts);

// читает из бинарного файла список товаров и возвращает их
order* rOrdersFromBinFile(char *fileName, size_t *countOrders);

// находит и возвращает позицию (индекс) товара в списке товаров
size_t searchIndProductFromArray(char *productName, product *arrayProducts,
                                 size_t sizeArray);

// записывает ненулевые (количество на складе > 0) товары в бинарный файл
void wNonZeroProductsToBinFile(char *fileName, product *arrayProducts,
                               size_t countProducts, size_t countZeroProducts);

#endif