#include "MatrixThread.hpp"

size_t line;
const size_t MAX_THREADS = 1024;

void* ThreadReduceLine(void* line_arg) {
    size_t line = *((size_t *) line_arg);

    double sum = 0.0;

    for (size_t j = 0; j < m_cols; j += 2)
        sum += (double) combinedMatrix.data[line][j] * combinedMatrix.data[line][j+1];

    reducedMatrix.data[line/b_cols][line%b_cols] = sum;

    pthread_exit(NULL);
}

void ThreadReduceMatrix() {
    size_t lines = combinedMatrix.lines;
    size_t interval = lines / MAX_THREADS + 1;

    pthread_t* th_ids = (pthread_t*) malloc(sizeof(pthread_t) * lines);

    for (size_t i = 0; i < lines; i += interval) {
        for (size_t k = i; k < i + interval; k++) {
            size_t *line = new size_t(k);

            if(pthread_create(&th_ids[i], NULL, ThreadReduceLine, line)) {
                cerr << "Failed creating thread " << i << endl;
                pthread_exit(NULL);
            }

        }

        for (size_t k = i; k < i + interval; k++)
            pthread_join(th_ids[i], NULL);
    }


    free(th_ids);
    th_ids = NULL;
}

void* ThreadCombineLine(void* bt_line_arg) {
    size_t bt_line = *((size_t *) bt_line_arg);
    size_t i = (line * BT.lines) + bt_line;
    size_t columns = BT.columns;

    for (size_t j = 0;  j < columns; j++) {
        combinedMatrix.data[i][j*2] = A.data[line][j];
        combinedMatrix.data[i][j*2 + 1] = BT.data[bt_line][j];
    }

    pthread_exit(NULL);
}

void ThreadCombineMatrices() {
    for(line = 0; line < A.lines; line++) {
        pthread_t* th_ids = (pthread_t*) malloc(sizeof(pthread_t) * BT.lines);

        for (size_t j = 0; j < BT.lines; j++) {
            size_t *bt_line = new size_t(j);

            if(pthread_create(&th_ids[j], NULL, ThreadCombineLine, bt_line)) {
                cerr << "Failed creating thread " << j << endl;
                pthread_exit(NULL);
            }

        }

        for (size_t j = 0; j < BT.lines; j++)
            pthread_join(th_ids[j], NULL);
    }
}

