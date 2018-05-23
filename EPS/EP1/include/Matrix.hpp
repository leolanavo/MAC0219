#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

class Matrix {
    public:
        unsigned long long lines;
        unsigned long long columns;
        double** data;

        Matrix();
        Matrix(unsigned long long x, unsigned long long y);
        Matrix(ifstream file, bool transpose);
};

#endif
