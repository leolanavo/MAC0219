#include "MatrixOpenMP.hpp"

void CombineLine(unsigned long long x, unsigned long long y) {
    unsigned long long i = (x * BT.lines) + y;
    unsigned long long columns = BT.columns;

    for (unsigned long long j = 0;  j < columns; j++) {
        combinedMatrix.data[i][j*2] = A.data[x][j];
        combinedMatrix.data[i][j*2 + 1] = BT.data[y][j];
    }
}

void ReduceLine(unsigned long long line) {
    double sum = 0.0;

    for (unsigned long long j = 0; j < m_cols; j += 2)
        sum += (double) combinedMatrix.data[line][j] * combinedMatrix.data[line][j+1];

    reducedMatrix.data[line/b_cols][line%b_cols] = sum;
}

void OMPCombineMatrices() {
    unsigned long long i, j;

    #pragma omp parallel num_threads(A.lines) private (i, j)
    {
        #pragma omp for schedule(dynamic, 1)
        for (i = 0; i < A.lines; i++)
            for (j = 0; j < BT.lines; j++) {
                CombineLine(i, j);
            }
    }
}

void OMPReduceMatrix() {
    unsigned long long i;
    unsigned long long lines = combinedMatrix.lines;

    #pragma omp parallel num_threads(combinedMatrix.lines) private(i)
    {
        for (i = 0; i < combinedMatrix.lines; i++)
            ReduceLine(i);
    }
}
