#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>

#include <omp.h>

#include "Matrix.hpp"
#include "MatrixThread.hpp"
#include "MatrixOpenMP.hpp"

#include "globals.hpp"

using namespace std;

int b_cols;
int m_cols;

Matrix combinedMatrix;
Matrix reducedMatrix;

Matrix A;
Matrix BT;

ostream& operator<<(ostream& os, Matrix& m) {
    for (int i = 0; i < m.lines; i++) {
        for (int j = 0; j < m.columns; j++) {
            os << m.data[i][j] << " ";
        }
        os << endl;
    }

    return os;
}

void CombineMatrices(Matrix& m1, Matrix& m2) {
    combinedMatrix = Matrix(m1.lines * m2.lines, m1.columns *  m2.columns);

    for (int i1 = 0; i1 < m1.lines; i1++)
        for (int i2 = 0; i2 < m2.lines; i2++)
            for (int j = 0; j < m1.columns; j++) {
                combinedMatrix.data[i1 * m2.lines + i2][j*2] = m1.data[i1][j];
                combinedMatrix.data[i1 * m2.lines + i2][j*2 + 1] = m2.data[i2][j];
            }
}


void ReduceCombinedMatrix(Matrix& m, int lines, int columns) {
    reducedMatrix = Matrix(lines, columns);

    int val;
    for (int i = 0; i < m.lines; i++) {
        val = 0;
        for (int j = 0; j < m.columns; j += 2)
            val += m.data[i][j] * m.data[i][j+1];
        reducedMatrix.data[i/columns][i%columns] = val;
    }
}

int main(int argc, char* argv[]) {
    string line;

    A = Matrix(ifstream(argv[1]), false);
    BT = Matrix(ifstream(argv[2]), true);

    reducedMatrix = Matrix(A.lines, BT.lines);
    combinedMatrix = Matrix(A.lines * BT.lines, A.columns * BT.columns);

    b_cols = BT.lines;
    m_cols = combinedMatrix.columns;

    if (stoi(argv[3]) == 1) {
        ThreadCombineMatrices();
        ThreadReduceMatrix();
    }
    else if (atoi(argv[3]) == 2) {
        OMPCombineMatrices();
        OMPReduceMatrix();
    }

    cout << combinedMatrix << endl;
    cout << reducedMatrix;

    return 0;
}
