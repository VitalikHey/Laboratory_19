#include "athlete.h"

void swapAthletes(athlete *const firstNum, athlete *const secondNum){
    athlete temp = *firstNum;
    *firstNum = *secondNum;
    *secondNum = temp;
}

int partitionAthletes(athlete arrayAthletes[], const int start, const int end){
    int pivot = arrayAthletes[end].value;
    int pivotIndex = start;
    for (int ind = start; ind < end; ind++){
        if (arrayAthletes[ind].value <= pivot){
            swapAthletes(&arrayAthletes[ind], &arrayAthletes[pivotIndex]);
            pivotIndex++;
        }
    }

    swapAthletes(&arrayAthletes[pivotIndex], &arrayAthletes[end]);
    return pivotIndex;
}

void quickSortAthletes(athlete arrayAthletes[], const int start, const int end){
    if (start >= end){
        return;
    }

    int pivot = partitionAthletes(arrayAthletes, start, end);
    quickSortAthletes(arrayAthletes, start, pivot - 1);
    quickSortAthletes(arrayAthletes, pivot + 1, end);
}