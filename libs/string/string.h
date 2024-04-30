#ifndef LABORATORY_19_STRING_H
#define LABORATORY_19_STRING_H

#include "stdio.h"
#include <stdbool.h>
#include <ctype.h>
#include <memory.h>

typedef struct WordDescriptor {
    char *begin; // позиция начала слова
    char *end; // позиция первого символа, после последнего символа слова
} WordDescriptor;

char* copy(const char *beginSource, const char *endSource,
           char *beginDestination);

char* getEndOfString(char* s);

int strcmp(const char *lhs, const char *rhs);

bool getWord(char *beginSearch, WordDescriptor *word);


#endif //LABORATORY_19_STRING_H
