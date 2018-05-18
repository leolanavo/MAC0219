#include "Matrix.hpp"

using namespace std;

Matrix::Matrix():
    lines(0), columns(0)
{
    data = NULL;
}

Matrix::Matrix(int x, int y):
    lines(x), columns(y)
{
    data = (float**) malloc(sizeof(float*) * lines);
    for (int i = 0; i < lines; i++) {
        data[i] = (float*) malloc(sizeof(float) * columns);
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

    data = (float**) malloc(sizeof(float*) * lines);
    for (int i = 0; i < lines; i++) {
        data[i] = (float*) malloc(sizeof(float) * columns);
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
