cmake_minimum_required(VERSION 3.26)
project(Laboratory_19 C)

set(CMAKE_C_STANDARD 11)

add_executable(Laboratory_19
        main.c
        libs/matrix/matrix.c
        libs/matrix/matrix.h
        libs/algorithms/algorithms.h
        libs/tasks/tasks.h
        libs/tasks/tasks.h
        libs/tasks/tasks.c
        libs/algorithms/algorithms.c
        libs/vector/vector.c
        libs/vector/vector.h
        libs/polynomial/polynomial.c
        libs/athlete/athlete.h
        libs/athlete/athlete.c
        libs/product/product.h
        libs/order/order.h
        libs/string/string.h
        libs/string/string.c
        libs/test/test.c
        libs/test/test.h
)
