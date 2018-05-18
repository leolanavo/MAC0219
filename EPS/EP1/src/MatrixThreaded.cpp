#include "MatrixThreaded.hpp"

void* ThreadedReduceCombinedLine(void* line_arg) {
    int line = *((int *) line_arg);

    float sum = 0.0;

    for (int j = 0; j < m_cols; j += 2)
        sum += combinedMatrix.data[line][j] * combinedMatrix.data[line][j+1];

    reducedMatrix.data[line/b_cols][line%b_cols] = sum;

    pthread_exit(NULL);
}

void ThreadedReduceCombinedMatrix(int b_cols) {
    int lines = combinedMatrix.lines;

    pthread_t* th_ids = (pthread_t*) malloc(sizeof(pthread_t) * lines);

    for (int i = 0; i < lines; i++) {
        int *line = new int(i);

        if(pthread_create(&th_ids[i], NULL, ThreadedReduceCombinedLine, line)) {
            cerr << "Failed creating thread " << i << endl;
            pthread_exit(NULL);
        }
    }

    for (int i = 0; i < lines; i++)
        pthread_join(th_ids[i], NULL);

    free(th_ids);
    th_ids = NULL;
}
