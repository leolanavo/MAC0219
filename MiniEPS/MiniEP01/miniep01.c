#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10000000

void seq_access (int* array) {
    for (int i = 0; i < SIZE; i++)
        array[i] += 1;
}

void rnd_access(int* array) {
    for (int i = 0; i < SIZE; i++) {
        int j = rand()%SIZE;
        array[j] += 1;
    }
}

double time_diff(clock_t a, clock_t b) {
        return (((double) (b - a)) / CLOCKS_PER_SEC);
}

double access(int* array, int flag) {
    clock_t start, end;

    char *fun = flag == 1? "Sequencial" : "Random";

    start = clock();
    if (flag == 1)
        seq_access(array);
    else
        rnd_access(array);
    end = clock();

    return(time_diff(start, end));
}

int main () {
    int* array = calloc(SIZE, sizeof(int));
    srand(time(NULL));

    double seq_time = access(array, 1);
    double rnd_time = access(array, 0);

    printf("Sequencial access took %f\n", seq_time);
    printf("Random access took %f\n", rnd_time);

    printf("The improvement is: %.2f%\n", (rnd_time/seq_time - 1) * 100);

    return 0;
}
