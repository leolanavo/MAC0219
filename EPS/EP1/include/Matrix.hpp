#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

class Matrix {
    public:
        Matrix() = default;
        Matrix(size_t x, size_t y);
        Matrix(const char *filename, bool transpose);

        size_t lines = 0;
        size_t columns = 0;
        double** data = nullptr;
};

#endif
