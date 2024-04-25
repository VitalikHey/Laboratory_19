#ifndef LABORATORY_19_VECTOR_H
#define LABORATORY_19_VECTOR_H


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct vector {
    int *data;
    size_t size;
    size_t capacity;
} vector;

vector createVector(size_t n);

void reserve(vector *v, size_t newCapacity);

void shrinkToFit(vector *v);

bool isFull(vector *v);

void pushBack(vector *v, int x);


#endif //LABORATORY_19_VECTOR_H
