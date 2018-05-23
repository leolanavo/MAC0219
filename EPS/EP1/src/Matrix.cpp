#include "Matrix.hpp"

using namespace std;

Matrix::Matrix():
    lines(0), columns(0)
{
    data = NULL;
}

Matrix::Matrix(unsigned long long x, unsigned long long y):
    lines(x), columns(y)
{
    data = (double**) malloc(sizeof(double*) * lines);
    for (unsigned long long i = 0; i < lines; i++) {
        data[i] = (double*) calloc(sizeof(double), columns);
    }
}

Matrix::Matrix(ifstream file, bool transpose) {
    string line;

    if (file.is_open()) {
        getline(file, line);
        istringstream iss(line);

        if (transpose)
            iss >> columns >> lines;
        else
            iss >> lines >> columns;
    } 
    else {
        cout << "File isn't open, ABORTING" << endl;
        exit(1);
    }

    data = (double**) malloc(sizeof(double*) * lines);
    for (unsigned long long i = 0; i < lines; i++) {
        data[i] = (double*) calloc(sizeof(double), columns);
    }

    int i, j;
    while (getline(file, line)) {
        istringstream iss(line);

        if (transpose)
            iss >> j >> i >> this->data[i][j];
        else
            iss >> i >> j >> this->data[i][j];
    }
}
