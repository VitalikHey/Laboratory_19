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

void wNumsToBinFile(char *fileName, int numsArray[], size_t sizeArray){
    FILE *file = openFile(fileName, "wb");

    fwrite(numsArray, sizeof(int), sizeArray, file);
    fclose(file);
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
