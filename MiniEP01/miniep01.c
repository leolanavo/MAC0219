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

void access(int* array, int flag) {
    clock_t start, end;

    char *fun = flag == 1? "Sequencial" : "Aleatória";

    start = clock();
    if (flag == 1)
        seq_access(array);
    else
        rnd_access(array);
    end = clock();

    printf("%s took %f\n", fun, time_diff(start, end));
}

int main () {
    int* array = calloc(SIZE, sizeof(int));
    srand(time(NULL));

    access(array, 1);
    access(array, 0);

    return 0;
}
