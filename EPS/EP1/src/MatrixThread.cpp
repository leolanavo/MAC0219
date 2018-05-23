#include "MatrixThread.hpp"

unsigned long long line;

void* ThreadReduceLine(void* line_arg) {
    unsigned long long line = *((unsigned long long *) line_arg);

    double sum = 0.0;

    for (unsigned long long j = 0; j < m_cols; j += 2)
        sum += (double) combinedMatrix.data[line][j] * combinedMatrix.data[line][j+1];

    reducedMatrix.data[line/b_cols][line%b_cols] = sum;

    pthread_exit(NULL);
}

void ThreadReduceMatrix() {
    unsigned long long lines = combinedMatrix.lines;

    pthread_t* th_ids = (pthread_t*) malloc(sizeof(pthread_t) * lines);

    for (unsigned long long i = 0; i < lines; i++) {
        unsigned long long *line = new unsigned long long(i);

        if(pthread_create(&th_ids[i], NULL, ThreadReduceLine, line)) {
            cerr << "Failed creating thread " << i << endl;
            pthread_exit(NULL);
        }
    }

    for (unsigned long long i = 0; i < lines; i++)
        pthread_join(th_ids[i], NULL);

    free(th_ids);
    th_ids = NULL;
}

void* ThreadCombineLine(void* bt_line_arg) {
    unsigned long long bt_line = *((unsigned long long *) bt_line_arg);
    unsigned long long i = (line * BT.lines) + bt_line;
    unsigned long long columns = BT.columns;

    for (unsigned long long j = 0;  j < columns; j++) {
        combinedMatrix.data[i][j*2] = A.data[line][j];
        combinedMatrix.data[i][j*2 + 1] = BT.data[bt_line][j];
    }

    pthread_exit(NULL);
}

void ThreadCombineMatrices() {
    for(line = 0; line < A.lines; line++) {
        pthread_t* th_ids = (pthread_t*) malloc(sizeof(pthread_t) * BT.lines);

        for (unsigned long long j = 0; j < BT.lines; j++) {
            unsigned long long *bt_line = new unsigned long long(j);

            if(pthread_create(&th_ids[j], NULL, ThreadCombineLine, bt_line)) {
                cerr << "Failed creating thread " << j << endl;
                pthread_exit(NULL);
            }

        }

        for (unsigned long long j = 0; j < BT.lines; j++)
            pthread_join(th_ids[j], NULL);
    }
}

