#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <pthread.h>

#include "Matrix.hpp"
#include "MatrixThreaded.hpp"

#include "globals.hpp"

using namespace std;

int b_cols;
int m_cols;

Matrix combinedMatrix;
Matrix reducedMatrix;

// The column of the super matrix is calculated with the j*2 and j*2 + 1
// The line of the super matrix is calculated with the line = (i1 * m2.lines) + i2
Matrix CombineMatrices(Matrix& m1, Matrix& m2) {
    Matrix result = Matrix(m1.lines * m2.lines, m1.columns *  m2.columns);

    for (int i1 = 0; i1 < m1.lines; i1++)
        for (int i2 = 0; i2 < m2.lines; i2++)
            for (int j = 0; j < m1.columns; j++) {
                result.data[i1 * m2.lines + i2][j*2] = m1.data[i1][j];
                result.data[i1 * m2.lines + i2][j*2 + 1] = m2.data[i2][j];
            }

    return result;
}


Matrix ReduceCombinedMatrix(Matrix& m, int lines, int columns) {
    Matrix result = Matrix(lines, columns);

    int val;
    for (int i = 0; i < m.lines; i++) {
        val = 0;
        for (int j = 0; j < m.columns; j += 2)
            val += m.data[i][j] * m.data[i][j+1];
        result.data[i/columns][i%columns] = val;
    }

    return result;
}


ostream& operator<<(ostream& os, Matrix& m) {
    for (int i = 0; i < m.lines; i++) {
        for (int j = 0; j < m.columns; j++) {
            os << m.data[i][j] << " ";
        }
        os << endl;
    }

    return os;
}

int main(int argc, char* argv[]) {
    string line;

    int proportion = atoi(argv[3]);

    Matrix a = Matrix(ifstream(argv[1]), false);
    Matrix bT = Matrix(ifstream(argv[2]), true);

    combinedMatrix = CombineMatrices(a, bT);
    reducedMatrix = Matrix(a.lines, bT.lines);

    b_cols = bT.lines;
    m_cols = combinedMatrix.columns;

    ThreadedReduceCombinedMatrix(bT.lines);

    cout << reducedMatrix;

    return 0;
}
