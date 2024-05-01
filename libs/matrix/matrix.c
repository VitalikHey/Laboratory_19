#include "matrix.h"


bool isMore(int firstNum, int secondNum){
    return firstNum > secondNum;
}


bool isLess(int firstNum, int secondNum){
    return firstNum < secondNum;
}


int getMax(int array[], int lengthArray){
    int maxNum = array[0];
    for (int ind = 1; ind < lengthArray; ind++){
        if (array[ind] > maxNum){
            maxNum = array[ind];
        }
    }

    return maxNum;
}


int getMin(int array[], int lengthArray){
    int minNum = array[0];
    for (int ind = 1; ind < lengthArray; ind++){
        if (array[ind] < minNum){
            minNum = array[ind];
        }
    }

    return minNum;
}


bool isUnique(int array[], int lengthArray){
    for (int indNum = 0; indNum < lengthArray - 1; indNum++){
        for (int indCheck = indNum + 1; indCheck < lengthArray; indCheck++){
            if (array[indNum] == array[indCheck]){
                return false;
            }
        }
    }

    return true;
}


position searchPosition(matrix m, bool (*predicate)(int, int)){
    if (m.nRows == 0){
        return (position){-1, -1};
    }

    position desiredPosition = {0, 0};
    int desiredValue = m.values[0][0];
    for (int indRow = 0; indRow < m.nRows; indRow++){
        for (int indCol = 0; indCol < m.nCols; indCol++){
            if (predicate(m.values[indRow][indCol], desiredValue)){
                desiredValue = m.values[indRow][indCol];
                desiredPosition.rowIndex = indRow;
                desiredPosition.colIndex = indCol;
            }
        }
    }

    return desiredPosition;
}


int getSum(int array[], int lengthArray){
    int sum = 0;
    for (size_t ind = 0; ind < lengthArray; ind++){
        sum += array[ind];
    }

    return sum;
}

// меняет значения по указателям firstNumber и secondNumber местами
void swap(int *const firstNum, int *const secondNum) {
    int temp = *firstNum;
    *firstNum = *secondNum;
    *secondNum = temp;
}

// сортирует числа в диапазоне [start, end] массива array
// вокруг опорного элемента pivot (по умолчанию крайнее правое число)
int partition(int array[], const int start, const int end, matrix m,
              void (*predicateSwap)(matrix, int, int)){
    int pivot = array[end];
    int pivotIndex = start;
    for (int ind = start; ind < end; ind++){
        if (array[ind] <= pivot){
            swap(&array[ind], &array[pivotIndex]);
            predicateSwap(m, ind, pivotIndex);
            pivotIndex++;
        }
    }

    swap(&array[pivotIndex], &array[end]);
    predicateSwap(m, pivotIndex, end);

    return pivotIndex;
}

// рекурсивно вызывает себя же для сортировки нового диапазона чисел
void quickSort(int array[], const int start, const int end, matrix m,
               void (*predicateSwap)(matrix, int, int)){
    if (start >= end){
        return;
    }

    int pivot = partition(array, start, end, m, predicateSwap);
    quickSort(array, start, pivot - 1, m, predicateSwap);
    quickSort(array, pivot + 1, end, m, predicateSwap);
}


matrix getMemMatrix(int nRows, int nCols) {
    int **values = (int **) malloc(sizeof(int*) * nRows);
    for (int i = 0; i < nRows; i++)
        values[i] = (int *) malloc(sizeof(int) * nCols);
    return (matrix){values, nRows, nCols};
}


matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols) {
    matrix *ms = (matrix*) malloc(sizeof(matrix) * nMatrices);
    for (int i = 0; i < nMatrices; i++)
        ms[i] = getMemMatrix(nRows, nCols);
    return ms;
}


void freeMemMatrix(matrix *m) {
    for (int ind = 0; ind < m->nRows; ind++) {
        free(m->values[ind]);
    }

    free(m->values);
    m->values = NULL;
}


void freeMemMatrices(matrix *ms, int nMatrices){
    for (int ind = 0; ind < nMatrices; ind++){
        freeMemMatrix(&ms[ind]);
    }
}


void inputMatrix(matrix *m){
    for (int indRow = 0; indRow < m->nRows; indRow++){
        for (int indCol = 0; indCol < m->nCols; indCol++){
            scanf("%d", &m->values[indRow][indCol]);
        }
    }
}


void inputMatrices(matrix *ms, int nMatrices){
    for (int ind = 0; ind < nMatrices; ind++){
        inputMatrix(&ms[ind]);
    }
}


void outputMatrix(matrix m){
    for (int indRow = 0; indRow < m.nRows; indRow++){
        for (int indCol = 0; indCol < m.nCols; indCol++){
            printf("%d ", m.values[indRow][indCol]);
        }

        printf("\n");
    }

    printf("\n");
}


void outputMatrices(matrix *ms, int nMatrices){
    for (int ind = 0; ind < nMatrices; ind++){
        outputMatrix(ms[ind]);
    }
}


void swapRows(matrix m, int i1, int i2){
    if (i1 >= m.nRows || i2 >= m.nRows){
        return;
    }

    int* temp = m.values[i1];
    m.values[i1] = m.values[i2];
    m.values[i2] = temp;
}


void swapColumns(matrix m, int j1, int j2){
    if (j1 >= m.nCols || j2 >= m.nCols){
        return;
    }

    for (int indRow = 0; indRow < m.nRows; indRow++){
        int temp = m.values[indRow][j1];
        m.values[indRow][j1] = m.values[indRow][j2];
        m.values[indRow][j2] = temp;
    }
}


void insertionSortRowsMatrixByRowCriteria(matrix m, int (*predicate)(int *, int)){
    int arrayResults[m.nRows];
    for (int ind = 0; ind < m.nRows; ind++){
        arrayResults[ind] = predicate(m.values[ind], m.nCols);
    }

    quickSort(arrayResults, 0, m.nRows - 1, m, swapRows);
}


void selectionSortColsMatrixByColCriteria(matrix m, int (*predicate)(int*, int)){
    int arrayResults[m.nCols];

    for (int indCol = 0; indCol < m.nCols; indCol++){
        int column[m.nRows];
        for (int indRow = 0; indRow < m.nRows; indRow++){
            column[indRow] = m.values[indRow][indCol];
        }

        arrayResults[indCol] = predicate(column, m.nRows);
    }

    quickSort(arrayResults, 0, m.nCols - 1, m, swapColumns);
}


bool isSquareMatrix(matrix *m){
    return m->nRows == m->nCols;
}


bool areTwoMatricesEqual(matrix *m1, matrix *m2){
    if (m1->nRows != m2->nRows || m1->nCols != m2->nCols){
        return false;
    }

    for (int indRow = 0; indRow < m1->nRows; indRow++){
        int resCheck = memcmp(m1->values[indRow],m2->values[indRow],
                              sizeof(int) * m1->nCols);
        if (resCheck){
            return false;
        }
    }

    return true;
}

bool isEMatrix(matrix *m){
    for (int ind = 0; ind < m->nRows; ind++){
        int sum = getSum(m->values[ind], m->nCols);
        if (sum != 1 || m->values[ind][ind]){
            return false;
        }
    }

    return true;
}


bool isSymmetricMatrix(matrix *m){
    if (!isSquareMatrix(m)){
        return false;
    }

    for (int indRow = 0; indRow < m->nRows; indRow++) {
        for (int indCol = indRow + 1; indCol < m->nCols; indCol++) {
            if (m->values[indRow][indCol] != m->values[indCol][indRow]) {
                return false;
            }
        }
    }

    return true;
}


void transposeSquareMatrix(matrix *m){
    for (int indRow = 0; indRow < m->nRows; indRow++){
        for (int indCol = indRow + 1; indCol < m->nCols; indCol++){
            int temp = m->values[indRow][indCol];
            m->values[indRow][indCol] = m->values[indCol][indRow];
            m->values[indCol][indRow] = temp;
        }
    }
}


void transposeMatrix(matrix *m){
    matrix newM = getMemMatrix(m->nCols, m->nRows);
    for (int indRow = 0; indRow < m->nRows; indRow++){
        for (int indCol = 0; indCol < m->nCols; indCol++){
            newM.values[indCol][indRow] = m->values[indRow][indCol];
        }
    }

    *m = newM;
}


position getMinValuePos(matrix m){
    return searchPosition(m, isLess);
}


position getMaxValuePos(matrix m){
    return searchPosition(m, isMore);
}


matrix createMatrixFromArray(const int *a, int nRows, int nCols) {
    matrix m = getMemMatrix(nRows, nCols);
    int k = 0;
    for (int i = 0; i < nRows; i++)
        for (int j = 0; j < nCols; j++)
            m.values[i][j] = a[k++];

    return m;
}


matrix *createArrayOfMatrixFromArray(const int *values, int nMatrices,
                                     int nRows, int nCols){
    matrix *ms = getMemArrayOfMatrices(nMatrices, nRows, nCols);
    int l = 0;
    for (size_t k = 0; k < nMatrices; k++)
        for (size_t i = 0; i < nRows; i++)
            for (size_t j = 0; j < nCols; j++)
                ms[k].values[i][j] = values[l++];

    return ms;
}