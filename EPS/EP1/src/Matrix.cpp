#include "Matrix.hpp"

using namespace std;

Matrix::Matrix(size_t x, size_t y):
    lines(x), columns(y)
{
    data = new double*[lines];
    for (size_t i = 0; i < lines; i++) {
        data[i] = new double[columns];
    }
}

Matrix::Matrix(const char *filename, bool transpose) {
    ifstream file(filename);
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

    data = new double*[lines];
    for (size_t i = 0; i < lines; i++) {
        data[i] = new double[columns];
    }

    int i, j;
    while (getline(file, line)) {
        istringstream iss(line);

        if (transpose)
            iss >> j >> i >> this->data[i-1][j-1];
        else
            iss >> i >> j >> this->data[i-1][j-1];
    }
}
