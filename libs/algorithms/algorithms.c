#include "algorithms.h"


void freeMemory(double **array, size_t size){
    *array = (double*)realloc(*array, size * sizeof(double));
}


FILE* openFile(char *fileName, char *action){
    FILE *file = fopen(fileName, action);

    if (file == NULL) {
        printf("Ошибка при открытии файла\n");
        exit(1);
    }

    return file;
}


void wArrayOfMatrix(char *fileName, matrix *ms, int nMatrices){
    FILE *file = openFile(fileName, "w");

    fprintf(file, "%d\n", nMatrices);

    if (nMatrices > 0){
        fprintf(file, "%d\n", ms->nRows);

        for (int indMatrix = 0; indMatrix < nMatrices; indMatrix++){
            for (int indRow = 0; indRow < ms->nRows; indRow++) {
                for (int indCol = 0; indCol < ms->nCols; indCol++) {
                    fprintf(file, "%d ", ms[indMatrix].values[indRow][indCol]);
                }
                fprintf(file, "\n");
            }
        }
    }

    fclose(file);
}


matrix *rMatrixFromFile(char *fileName, int *rCountMatrices) {
    FILE *file = openFile(fileName, "r");

    int nMatrices;
    matrix *ms;
    fscanf(file, "%d", &nMatrices);

    if (nMatrices > 0){
        int dimensionMatrices;
        fscanf(file, "%d", &dimensionMatrices);

        ms = getMemArrayOfMatrices(nMatrices,
                                   dimensionMatrices,
                                   dimensionMatrices);

        for (int indMatrix = 0; indMatrix < nMatrices; indMatrix++){
            for (int indRow = 0; indRow < dimensionMatrices; indRow++){
                for (int indCol = 0; indCol < dimensionMatrices; indCol++){
                    fscanf(file, "%d", &ms[indMatrix].values[indRow][indCol]);
                }
            }
        }
    }

    *rCountMatrices = nMatrices;
    fclose(file);

    return ms;
}


void rNumsFromFile(char *fileName, double array[], size_t *sizeArray){
    FILE *file = openFile(fileName, "r");

    size_t ind = 0;
    while (fscanf(file, "%lf", &array[ind]) == 1) {
        ind++;

        if (ind == *sizeArray){
            *sizeArray *= 2;
            array = (double*)realloc(array, *sizeArray * sizeof(double));
        }
    }

    freeMemory(&array, ind);
    *sizeArray = ind;
    fclose(file);
}


void wNumsToFile(char *fileName, double array[], size_t lengthArray){
    FILE *file = openFile(fileName, "w");

    for (int ind = 0; ind < lengthArray; ind++){
        fprintf(file, "%.2f\n", array[ind]);
    }

    fclose(file);
}


double makeOperation(double firstNum, double secondNum, char operation){
    double result;
    if (operation == '/'){
        if (secondNum == 0){
            printf("ERROR - деление на 0");
            exit(1);
        }
        result = firstNum / secondNum;
    } else if (operation == '*'){
        result = firstNum * secondNum;
    } else if (operation == '-'){
        result = firstNum - secondNum;
    } else {
        result = firstNum + secondNum;
    }

    return result;
}


double calculate(double nums[], char operations[], size_t indOperations){
    double result;

    if (indOperations == 1){
        result = makeOperation(nums[0], nums[1], operations[0]);
    } else{
        if ((operations[0] == '+' || operations[0] == '-') &&
            (operations[1] == '*' || operations[1] == '/')){
            result = makeOperation(nums[0], makeOperation(nums[1], nums[2],
                                   operations[1]), operations[0]);
        } else{
            result = makeOperation(makeOperation(nums[0], nums[1],
                                   operations[0]), nums[2], operations[1]);
        }
    }

    return result;
}


void calculateArithmeticExpression(char *fileName, double *result){
    FILE *file = openFile(fileName, "r");

    double nums[5];
    char operations[5];
    size_t indNums = 0;
    size_t indOperations = 0;
    char c;
    while (fscanf(file, "%c", &c) == 1) {
        if (isdigit(c)){
            nums[indNums++] = c - '0';
        } else if (c == '+' || c == '-' || c == '*' || c == '/'){
            operations[indOperations++] = c;
        }
    }

    *result = calculate(nums, operations, indOperations);
    fclose(file);
}


void wStringToFile(char *fileName, char *s){
    FILE *file = openFile(fileName, "w");
    fprintf(file, "%s", s);
    fclose(file);
}


bool wordIncludesSequence(WordDescriptor word, char* sequence,
                          size_t sizeSequence){
    size_t indSequence = 0;
    while (word.begin != word.end && indSequence < sizeSequence){
        if (*word.begin == sequence[indSequence]){
            indSequence++;
        } else{
            indSequence = 0;
        }

        word.begin++;
    }

    return indSequence == sizeSequence;
}


void rFilterWordsFromFile(char *fileName, char *newS, char *desiredSequence,
                          size_t sizeSequence){
    FILE *file = openFile(fileName, "r");
    char word[50];
    char *startWord = word;
    char *beginWord = word;

    char *begin = newS;
    char *start = newS;
    WordDescriptor dWord;
    while (fscanf(file, "%s", word) != EOF) {
        dWord.begin = startWord;
        dWord.end = getEndOfString(beginWord);
        if (wordIncludesSequence(dWord, desiredSequence, sizeSequence)){
            begin = copy(dWord.begin, dWord.end, begin);
            *begin = ' ';
            begin++;
        }
    }

    if (begin != start){
        *(--begin) = '\0';
    } else{
        *begin = '\0';
    }

    fclose(file);
}


void getLongestWordsInLineFromFile(char *fileName, char *result){
    FILE *file = openFile(fileName, "r");

    char* beginResult = result;
    char line[200];
    while (fgets(line, 200, file) != NULL){
        char* begin = line;

        WordDescriptor lookingWord;
        size_t sizeLookingWord = 0;
        WordDescriptor word;
        while (getWord(begin, &word)){
            size_t sizeWord = word.end - word.begin;
            if (sizeWord > sizeLookingWord){
                sizeLookingWord = sizeWord;
                lookingWord = word;
            }

            begin = word.end;
        }

        if (sizeLookingWord > 0){
            beginResult = copy(lookingWord.begin, lookingWord.end, beginResult);
            *beginResult = '\n';
            beginResult++;
        }
    }

    fclose(file);
}


void wPolyToFile(char *fileName, int powers[], double factors[],
                 int monAmounts[], int polAmount){
    polynomial *ps = createPolynomialsFromArray(
            powers, factors,
            monAmounts, polAmount);

    FILE *f = openFile(fileName, "wb");

    savePolynomials(ps, f, polAmount);

    fclose(f);
}


polynomial* rPolyFromFile(char *fileName){
    FILE *f = openFile(fileName, "rb");

    int polAmount;
    polynomial *ps = loadPolynomials(f, &polAmount);
    fclose(f);
    return ps;
}


int sortedPoly(polynomial* ps, int x, int polAmount){
    int i = 0;
    while (i < polAmount){
        if (fabs(calculatePolynomial(ps[i], x)) < 0.00001) {
            freePolynomial(ps + i);
            ps[i] = ps[--polAmount];
        }
        else
            i++;
    }

    return i;
}


void savePolyResult(char *fileName, polynomial *ps, int polAmount){
    FILE* file = openFile(fileName, "wb");
    savePolynomials(ps, file, polAmount);
    fclose(file);
}


void wNumsToBinFile(char *fileName, int numsArray[], size_t sizeArray){
    FILE *file = openFile(fileName, "wb");

    fwrite(numsArray, sizeof(int), sizeArray, file);
    fclose(file);
}


void rFilterAndWriteNumsFromBinFile(char *fileName,
                                    vector *positive,
                                    vector *negative){
    FILE *file = openFile(fileName, "rb");

    size_t indPositive = 0;
    size_t indNegative = 0;

    int num;
    while (fread(&num, sizeof(int), 1, file) == 1){
        if (num > 0){
            pushBack(positive, num);
        } else{
            pushBack(negative, num);
        }
    }

    fclose(file);

    wNumsToBinFile(fileName, positive->data, indPositive);
    wNumsToBinFile(fileName, negative->data, indNegative);

    shrinkToFit(positive);
    shrinkToFit(negative);
}


void wMatrixToBinFile(char *fileName, matrix *ms, int nMatrices) {
    FILE *file = openFile(fileName, "wb");

    fwrite(&nMatrices, sizeof(int), 1, file);
    if (nMatrices > 0){
        fwrite(&ms[0].nRows, sizeof(int), 1, file);

        for (int indMatrix = 0; indMatrix < nMatrices; indMatrix++) {
            for (int indRow = 0; indRow < ms[indMatrix].nRows; indRow++) {
                fwrite(ms[indMatrix].values[indRow], sizeof(int),
                       ms[indMatrix].nCols, file);
            }
        }
    }

    fclose(file);
}


matrix* rMatrixFromBinFile(char *fileName) {
    FILE *file = openFile(fileName, "rb");
    int nMatrices;
    fread(&nMatrices, sizeof(int), 1, file);
    matrix *ms;

    if (nMatrices > 0){
        int dimensionMatrices;
        fread(&dimensionMatrices, sizeof(int), 1, file);
        ms = getMemArrayOfMatrices(nMatrices,
                                   dimensionMatrices,
                                   dimensionMatrices);

        for (int indMatrix = 0; indMatrix < nMatrices; indMatrix++) {
            for (int indRow = 0; indRow < ms[indMatrix].nRows; indRow++) {
                fread(ms[indMatrix].values[indRow], sizeof(int),
                      ms[indMatrix].nCols, file);
            }
        }
    }

    fclose(file);
    return ms;
}


void wAthletesToBinFile(char *fileName, athlete *arrayAthletes,
                        int countAthletes){
    FILE *file = openFile(fileName, "wb");
    fwrite(&countAthletes, sizeof(int), 1, file);

    for (size_t athleteIndex = 0; athleteIndex < countAthletes; athleteIndex++){
        fwrite(&arrayAthletes[athleteIndex], sizeof(athlete), 1, file);
    }

    fclose(file);
}


athlete rAthleteInfoFromBinFile(FILE *file){
    athlete info;
    fread(&info, sizeof(athlete), 1, file);
    return info;
}


athlete* rAthletesFromBinFile(char *fileName, int *countAthletes){
    FILE *file = openFile(fileName, "rb");

    fread(countAthletes, sizeof (int), 1, file);
    athlete *buffer = malloc(*countAthletes * sizeof(athlete));
    for (size_t athleteIndex = 0; athleteIndex < *countAthletes; athleteIndex++){
        buffer[athleteIndex] = rAthleteInfoFromBinFile(file);
    }

    fclose(file);
    return buffer;
}


void wProductsToBinFile(char *fileName, product *arrayProducts,
                        size_t countProducts){
    FILE *file = openFile(fileName, "wb");
    fwrite(&countProducts, sizeof(size_t), 1, file);

    for (size_t productIndex = 0; productIndex < countProducts; productIndex++){
        fwrite(&arrayProducts[productIndex], sizeof(product), 1, file);
    }

    fclose(file);
}


void wOrdersToBinFile(char *fileName, order *arrayOrders, size_t countOrders){
    FILE *file = openFile(fileName, "wb");

    fwrite(&countOrders, sizeof(size_t), 1, file);

    for (size_t orderIndex = 0; orderIndex < countOrders; orderIndex++){
        fwrite(&arrayOrders[orderIndex], sizeof(order), 1, file);
    }

    fclose(file);
}


product rProductInfoFromBinFile(FILE *file){
    product info;
    fread(&info, sizeof(product), 1, file);
    return info;
}


product* rProductsFromBinFile(char *fileName, size_t *countProducts){
    FILE *file = openFile(fileName, "rb");

    fread(countProducts, sizeof(size_t), 1, file);
    product *buffer = malloc(*countProducts * sizeof(product));
    for (size_t productIndex = 0; productIndex < *countProducts; productIndex++){
        buffer[productIndex] = rProductInfoFromBinFile(file);
    }

    fclose(file);
    return buffer;
}


order rOrderInfoFromBinFile(FILE *file){
    order info;
    fread(&info, sizeof(order), 1, file);
    return info;
}


order* rOrdersFromBinFile(char *fileName, size_t *countOrders){
    FILE *file = openFile(fileName, "rb");

    fread(countOrders, sizeof(size_t), 1, file);
    order *buffer = malloc(*countOrders * sizeof(order));
    for (size_t orderIndex = 0; orderIndex < *countOrders; orderIndex++){
        buffer[orderIndex] = rOrderInfoFromBinFile(file);
    }

    fclose(file);
    return buffer;
}


size_t searchIndProductFromArray(char *productName, product *arrayProducts,
                                 size_t sizeArray){
    for (size_t ind = 0; ind < sizeArray; ind++){
        if (strcmp(productName, arrayProducts[ind].productName) == 0){
            return ind;
        }
    }
}


void wNonZeroProductsToBinFile(char *fileName, product *arrayProducts,
                               size_t countProducts, size_t countZeroProducts){
    FILE *file = openFile(fileName, "wb");
    size_t countNonZeroProducts = countProducts - countZeroProducts;
    fwrite(&countNonZeroProducts, sizeof(size_t), 1, file);

    for (size_t productIndex = 0; productIndex < countProducts; productIndex++){
        if (arrayProducts[productIndex].count > 0){
            fwrite(&arrayProducts[productIndex], sizeof(product), 1, file);
        }
    }

    fclose(file);
}