#include "MatrixOpenMP.hpp"

void CombineLine(size_t x, size_t y) {
    size_t i = (x * BT.lines) + y;
    size_t columns = BT.columns;

    for (size_t j = 0;  j < columns; j++) {
        combinedMatrix.data[i][j*2] = A.data[x][j];
        combinedMatrix.data[i][j*2 + 1] = BT.data[y][j];
    }
}

void ReduceLine(size_t line) {
    double sum = 0.0;

    for (size_t j = 0; j < m_cols; j += 2)
        sum += (double) combinedMatrix.data[line][j] * combinedMatrix.data[line][j+1];

    reducedMatrix.data[line/b_cols][line%b_cols] = sum;
}

void OMPCombineMatrices() {
    size_t i, j;

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
    size_t i;
    size_t lines = combinedMatrix.lines;

    #pragma omp parallel num_threads(combinedMatrix.lines) private(i)
    {
        for (i = 0; i < combinedMatrix.lines; i++)
            ReduceLine(i);
    }
}
