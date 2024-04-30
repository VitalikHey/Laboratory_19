#ifndef LABORATORY_19_ATHLETE_H
#define LABORATORY_19_ATHLETE_H

typedef struct athlete {
    char *fullName; // ФИО спортсмена
    int value; // лучший результат спортсмена
} athlete;

void quickSortAthletes(athlete arrayAthletes[], const int start, const int end);

#endif //LABORATORY_19_ATHLETE_H
