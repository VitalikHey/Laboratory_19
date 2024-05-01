#include "test.h"

void allTests() {
    testFirstTask();
    testSecondTask();
    testThirdTask();
    testFourthTask();
    testFifthTask();
    testSixthTask();
    testSeventhTask();
    testEighthTask();
    testNinthTask();
    testTenthTask();
}

bool comp(double firstNum, double secondNum){
    return (fabs(firstNum - secondNum) < 0.01);
}


void testFirstTaskWithNonEmptyMatrices(){
    char fileName1[50] = "../firstTask1.txt";
    int nMatrices1 = 4;
    matrix *ms1 = createArrayOfMatrixFromArray(
            (int[]) {
                    7, 1,
                    1, 1,

                    1, 6,
                    2, 2,

                    5, 4,
                    2, 3,

                    1, 3,
                    7, 9
            }, nMatrices1, 2, 2
    );

    firstTask(fileName1, ms1, nMatrices1);

    int rCountMatrices1;
    matrix *result1 = rMatrixFromFile(fileName1, &rCountMatrices1);

    assert(nMatrices1 == rCountMatrices1);

    matrix *expected1 = createArrayOfMatrixFromArray(
            (int[]) {
                    7, 1,
                    1, 1,

                    1, 2,
                    6, 2,

                    5, 2,
                    4, 3,

                    1, 7,
                    3, 9
            }, nMatrices1, 2, 2
    );

    for (int indMatrix = 0; indMatrix < rCountMatrices1; indMatrix++){
        assert(areTwoMatricesEqual(&result1[indMatrix], &expected1[indMatrix]));
    }
}


void testFirstTaskWithEmptyMatrices(){
    char fileName2[50] = "../firstTask2.txt";
    int nMatrices2 = 0;
    matrix *ms2 = createArrayOfMatrixFromArray(
            (int[]) {}, nMatrices2, 0, 0
    );

    firstTask(fileName2, ms2, nMatrices2);

    int rCountMatrices2;
    matrix *result2 = rMatrixFromFile(fileName2, &rCountMatrices2);

    assert(nMatrices2 == rCountMatrices2);

    matrix *expected2 = createArrayOfMatrixFromArray(
            (int[]) {}, nMatrices2, 0, 0
    );

    for (int indMatrix = 0; indMatrix < rCountMatrices2; indMatrix++){
        assert(areTwoMatricesEqual(&result2[indMatrix], &expected2[indMatrix]));
    }
}


void testFirstTask(){
    testFirstTaskWithNonEmptyMatrices();
    testFirstTaskWithEmptyMatrices();
}


void testSecondTaskWithNonEmptyArray(){
    char *fileName = "../secondTask1.txt";
    double arrayNums[17] = {1, 2, 3, 4, 5, 6, 7,
                            8,9, 10.111, 11.121212, 12,
                            13,14, 15, 16, 17};
    size_t sizeArray = 17;

    size_t newArraySize = 16;
    double *newArray = secondTask(fileName, arrayNums, sizeArray, &newArraySize);

    double exception[17] = {1.00, 2.00, 3.00, 4.00, 5.00, 6.00, 7.00,
                            8.00,9.00, 10.11, 11.12, 12.00,
                            13.00,14.00, 15.00, 16.00, 17.00};

    assert(newArraySize == sizeArray);

    for (int ind = 0; ind < sizeArray; ind++){
        assert(comp(newArray[ind], exception[ind]));
    }
}


void testSecondTaskWithEmptyArray(){
    char *fileName = "../secondTask2.txt";
    double arrayNums[0];
    size_t sizeArray = 0;

    size_t newArraySize = 16;
    double *newArray = secondTask(fileName, arrayNums, sizeArray, &newArraySize);

    double exception[0];

    assert(newArraySize == sizeArray);

    for (int ind = 0; ind < sizeArray; ind++){
        assert(comp(newArray[ind], exception[ind]));
    }
}


void testSecondTask(){
    testSecondTaskWithNonEmptyArray();
    testSecondTaskWithEmptyArray();
}


void testThirdTask(){
    char *fileName = "../thirdTask.txt";
    char s[100] = "9 - 9 * 0";
    double result;
    thirdTask(fileName, s, &result);

    assert(comp(result, 9));
}


void testFourthTask(){
    char *fileName = "../fourthTask.txt";
    char s[200] = "abcde abc ade res bc chaiok pirozhok vkusno";
    char desiredSequence[5] = "bc";
    size_t sizeSequence = 2;

    char got[1000];
    fourthTask(fileName, s, desiredSequence, sizeSequence, got);
    char expected[1000] = "abcde abc bc";
    assert(strcmp(got, expected) == 0);
}


void testFifthTask(){
    char *fileName = "../fifthTask.txt";
    char s[200] = "abc def\nab\npivo kozel";

    char got[200];
    fifthTask(fileName, s, got);
    char expected[200] = "abc\nab\nkozel\n";
    assert(strcmp(got, expected) == 0);
}


void testSixthTask(){
    char *fileName = "../sixthTask.txt";
    double factors[] = {1.0, -7.0, 10.0, 1.0, -2.0, 1.0};
    int powers[] = {3, 2, 0, 2, 1, 0};
    int monAmounts[] = {3, 3};
    int polAmount = 2;
    int x = 1;

    int got;
    sixthTask(fileName, powers, factors, monAmounts, polAmount, x, &got);
    int expected = 1;
    assert(got == expected);
}


void testSeventhTask(){
    char *fileName = "../seventhTask.txt";
    int numsArray[10] = {2, -4, -5, -6, -8, 3, 1, 7, -2, 9};
    size_t sizeArray = 10;

    vector positive = createVector(1);
    vector negative = createVector(1);

    seventhTask(fileName, numsArray, sizeArray, &positive, &negative);

    int expectedPositive[5] = {2, 3, 1, 7, 9};
    int expectedNegative[5] = {-4, -5, -6, -8, -2};

    assert(positive.size == 5);
    assert(negative.size == 5);

    for (size_t indPositive = 0; indPositive < positive.size; indPositive++){
        assert(positive.data[indPositive] == expectedPositive[indPositive]);
    }

    for (size_t indNegative = 0; indNegative < negative.size; indNegative++){
        assert(negative.data[indNegative] == expectedNegative[indNegative]);
    }
}


void testEighthTask(){
    char *fileName = "../eighthTask.txt";

    int nMatrices = 3;
    int n = 3; // подрядок матриц
    matrix *ms = createArrayOfMatrixFromArray(
            (int[]) {
                    1, 3, 0,
                    3, 2, 6,
                    0, 6, 5,

                    1, 0, 0,
                    0, 1, 0,
                    0, 0, 1,

                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 9
            }, nMatrices, n, n
    );

    eighthTask(fileName, ms, nMatrices);

    matrix *expected = createArrayOfMatrixFromArray(
            (int[]) {
                    1, 3, 0,
                    3, 2, 6,
                    0, 6, 5,

                    1, 0, 0,
                    0, 1, 0,
                    0, 0, 1,

                    1, 4, 7,
                    2, 5, 8,
                    3, 6, 9
            }, nMatrices, n, n
    );

    matrix *get = rMatrixFromBinFile(fileName);

    for (size_t indMatrix = 0; indMatrix < nMatrices; indMatrix++){
        assert(areTwoMatricesEqual(&get[indMatrix], &expected[indMatrix]));
    }
}


void testNinthTask(){
    char *fileName = "../ninthTask.txt";
    int countAthletes = 4;
    athlete arrayAthletes[countAthletes];

    arrayAthletes[0].fullName = "Иванов Иван Иванович";
    arrayAthletes[0].value = 100;

    arrayAthletes[1].fullName = "Петров Петр Петрович";
    arrayAthletes[1].value = 200;

    arrayAthletes[2].fullName = "Сидоров Сидор Сидорович";
    arrayAthletes[2].value = 150;

    arrayAthletes[3].fullName = "Базанов Алексей Петрович";
    arrayAthletes[3].value = 300;

    int needAthletes = 2;
    athlete rArrayAthletes[4];
    athlete *rightAthletes;

    ninthTask(fileName, arrayAthletes, countAthletes, needAthletes,
              rArrayAthletes, &rightAthletes);

    int expected[2] = {200, 300};
    for (size_t ind = 0; ind < needAthletes; ind++){
        assert(rightAthletes[ind].value == expected[ind]);
    }
}


void testTenthTask(){
    char *fileNameProducts = "../tenthTaskProducts.txt";
    char *fileNameOrders = "../tenthTaskOrders.txt";

    size_t countProducts = 3;
    product arrayProducts[countProducts];

    arrayProducts[0].productName = "Тапочки";
    arrayProducts[0].count = 4;
    arrayProducts[0].pricePerUnit = 5;
    arrayProducts[0].allPrice = 20;

    arrayProducts[1].productName = "Лимонадик";
    arrayProducts[1].count = 3;
    arrayProducts[1].pricePerUnit = 2;
    arrayProducts[1].allPrice = 6;

    arrayProducts[2].productName = "Квас";
    arrayProducts[2].count = 5;
    arrayProducts[2].pricePerUnit = 3;
    arrayProducts[2].allPrice = 15;

    size_t countOrders = 3;
    order arrayOrders[countOrders];

    arrayOrders[0].productName = "Квас";
    arrayOrders[0].count = 5;

    arrayOrders[1].productName = "Лимонадик";
    arrayOrders[1].count = 2;

    arrayOrders[2].productName = "Тапочки";
    arrayOrders[2].count = 1;

    product *rArrayProductsIndicator;

    tenthTask(fileNameProducts, fileNameOrders, arrayProducts, countProducts,
              arrayOrders, countOrders, &rArrayProductsIndicator);

    size_t expectedCount[3] = {3, 1, 0};
    size_t expectedAllPrice[3] = {15, 2, 0};

    for (size_t indProducts = 0; indProducts < countProducts; indProducts++){
        assert(rArrayProductsIndicator[indProducts].count ==
               expectedCount[indProducts]);
        assert(rArrayProductsIndicator[indProducts].allPrice ==
               expectedAllPrice[indProducts]);
    }
}
