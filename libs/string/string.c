#include "string.h"


char* copy(const char *beginSource, const char *endSource,
           char *beginDestination){
    memcpy(beginDestination, beginSource, endSource - beginSource);

    return beginDestination + (endSource - beginSource);
}


char* getEndOfString(char* s){
    while (*s != '\0'){
        s++;
    }

    return s;
}


int strcmp(const char *lhs, const char *rhs){
    while (*lhs == *rhs && *lhs != '\0' && *rhs != '\0'){
        lhs++;
        rhs++;
    }

    return *lhs - *rhs;
}


char* findNonSpace(char *begin){
    while (isspace(*begin))
        begin++;

    return begin;
}


char* findSpace(char *begin){
    while (!isspace(*begin) && *begin != '\0')
        begin++;

    return begin;
}


bool getWord(char *beginSearch, WordDescriptor *word) {
    word->begin = findNonSpace(beginSearch);
    if (*word->begin == '\0')
        return false;
    word->end = findSpace(word->begin);

    return true;
}
