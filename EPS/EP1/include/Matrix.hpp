#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

class Matrix {
    public:
        int lines;
        int columns;
        double** data;

        Matrix();
        Matrix(int x, int y);
        Matrix(ifstream file, bool transpose);
};

#endif
