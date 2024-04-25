#include "polynomial.h"
#include <malloc.h>


polynomial createPolynomialFromArray(int powers[], double factors[], int argsAmount){
    polynomial p;
    p.monomial_amount = argsAmount;
    p.data = (monomial*) malloc(argsAmount * sizeof(monomial));

    for (int i = 0; i < argsAmount; ++i) {
        p.data[i].factor = factors[i];
        p.data[i].power = powers[i];
    }

    return p;
}


polynomial* createPolynomialsFromArray(int powers[], double factors[],
                                       int monAmount[], int polAmount){
    polynomial *buffer = malloc(polAmount * sizeof(polynomial));
    for (int polIndex = 0; polIndex < polAmount; ++polIndex) {
        buffer[polIndex] = createPolynomialFromArray(
                powers, factors, monAmount[polIndex]);

        powers += monAmount[polIndex];
        factors += monAmount[polIndex];
    }

    return buffer;
}


polynomial loadPolynomial(FILE *f){
    polynomial p;
    fread(&p, sizeof(polynomial), 1, f);

    p.data = (monomial*) malloc(p.monomial_amount * sizeof (monomial));

    fread(p.data, sizeof (monomial), p.monomial_amount, f);

    return p;
}


polynomial* loadPolynomials(FILE *f, int *polAmount){
    fread(polAmount, sizeof (int), 1, f);

    polynomial *buffer = malloc(*polAmount * sizeof(polynomial));
    for (int polIndex = 0; polIndex < *polAmount; ++polIndex) {
        buffer[polIndex] = loadPolynomial(f);
    }

    return buffer;
}


void savePolynomial(polynomial p, FILE *f){
    fwrite(&p, sizeof(polynomial), 1, f);
    fwrite(p.data, sizeof (monomial), p.monomial_amount, f);
}


void savePolynomials(polynomial *ps, FILE *f, int pol_amount){
    fwrite(&pol_amount, sizeof (int), 1, f);

    for (int pol_index = 0; pol_index < pol_amount; ++pol_index) {
        savePolynomial(ps[pol_index], f);
    }
}


double calculatePolynomial(polynomial p, double x){
    double result = 0;
    double mul = 1;
    int index = p.monomial_amount - 1;

    for (int power = 0; power <= p.data[0].power; power++){
        if (p.data[index].power == power) {
            result += p.data[index].factor * mul;
            index--;
        }
        mul *= x;
    }

    return result;
}


void freePolynomial(polynomial* p){
    free(p->data);
    p->data = NULL;
    p->monomial_amount = 0;
}
