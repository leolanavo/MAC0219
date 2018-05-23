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

ofstream& operator<<(ofstream& fs, Matrix& m) {
    for (int i = 0; i < m.lines; i++)
        for (int j = 0; j < m.columns; j++)
            if (m.data[i][j] != 0)
                fs << i << " " << j << " " << m.data[i][j] << endl;

    return fs;
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
    ofstream output_file;

    A = Matrix(ifstream(argv[ARG_INF1]), false);
    BT = Matrix(ifstream(argv[ARG_INF2]), true);

    reducedMatrix = Matrix(A.lines, BT.lines);
    combinedMatrix = Matrix(A.lines * BT.lines, A.columns * BT.columns);

    b_cols = BT.lines;
    m_cols = combinedMatrix.columns;

    if (argv[ARG_IMP][0] == 'o') {
        ThreadCombineMatrices();
        ThreadReduceMatrix();
    }
    else if (argv[ARG_IMP][0] == 'p') {
        OMPCombineMatrices();
        OMPReduceMatrix();
    }

    cout << combinedMatrix << endl;
    cout << reducedMatrix;

    output_file.open(argv[ARG_OUTF]);
    output_file << reducedMatrix << endl;
    output_file.close();

    return 0;
}
