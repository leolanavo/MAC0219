#include "MatrixOpenMP.hpp"

void CombineLine(int x, int y) {
    int i = (x * BT.lines) + y;
    int columns = BT.columns;

    for (int j = 0;  j < columns; j++) {
        combinedMatrix.data[i][j*2] = A.data[x][j];
        combinedMatrix.data[i][j*2 + 1] = BT.data[y][j];
    }
}

void ReduceLine(int line) {
    float sum = 0.0;

    for (int j = 0; j < m_cols; j += 2)
        sum += combinedMatrix.data[line][j] * combinedMatrix.data[line][j+1];

    reducedMatrix.data[line/b_cols][line%b_cols] = sum;
}

void OMPCombineMatrices() {
    int i, j;

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
    int i;
    int lines = combinedMatrix.lines;

    #pragma omp parallel num_threads(combinedMatrix.lines) private(i)
    {
        for (i = 0; i < combinedMatrix.lines; i++)
            ReduceLine(i);
    }
}
