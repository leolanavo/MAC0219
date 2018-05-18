#ifndef _MY_THREAD_HPP
#define _MY_THREAD_HPP

#include "matrix.hpp"

typedef struct {
    int x;
    int y;
    float ai;
    float bj;
    Matrix target;
} *params;

void *combineUnit(void *);

#endif