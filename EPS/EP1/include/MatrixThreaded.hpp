#ifndef __MATRIX_THREADED_HPP__
#define __MATRIX_THREADED_HPP__

#include <pthread.h>
#include "globals.hpp"

void* ThreadedReduceCombinedLine(void* line_arg);

void ThreadedReduceCombinedMatrix(int b_cols);

void* ThreadedCombineLines(void* bt_line_arg);

void ThreadedCombineMatrices();

#endif
