#ifndef INC_POLYNOMIAL_H
#define INC_POLYNOMIAL_H

#include <stdio.h>

typedef struct monomial{
    int power;
    double factor;
} monomial;


typedef struct polynomial{
    int monomial_amount;
    struct monomial *data;
} polynomial;


// Для тестирования, аргументы должны передаваться по убыванию степеней
polynomial createPolynomialFromArray(int powers[], double factors[], int argsAmount);

polynomial* createPolynomialsFromArray(int powers[], double factors[],
                                       int monAmount[], int polAmount);

polynomial loadPolynomial(FILE *f);

polynomial* loadPolynomials(FILE *f, int *polAmount);

void savePolynomial(polynomial p, FILE *f);

void savePolynomials(polynomial *ps, FILE *f, int pol_amount);

double calculatePolynomial(polynomial p, double x);

void freePolynomial(polynomial* p);

#endif
