#include <cstdio>
#include <cstdlib>
#include <time.h>

#define SIZE 1000000

using namespace std;

void access_with_threshold(int array[], double threshold) {
    for (int i = 0; i < SIZE; i++) {
        if (rand()/(double) RAND_MAX <= threshold)
            array[i]++;
        else
            array[i]++;
    }

}

double time_diff(clock_t start, clock_t end) {
        return (((double) (end - start)) / CLOCKS_PER_SEC);
}

double access(int array[], int flag) {
    clock_t start, end;

    const char* fun = flag == 1? "Fixed" : "Variant";
    double threshold = flag == 1? 1 :  rand()/(double)RAND_MAX;
    printf("Threshold: %f\n", threshold);

    start = clock();
    access_with_threshold(array, threshold);
    end = clock();

    return(time_diff(start, end));
}

int main() {
    int array[SIZE];
    srand(time(NULL));

    for (int i = 0; i < SIZE; i++)
        array[i] = 0;

    double fixed_time = access(array, 1); 
    double var_time = access(array, 0); 
    printf("Fix: %f | Var: %f\n", fixed_time, var_time);
    
    printf("The difference is: %f%\n", (var_time/fixed_time - 1) * 100);

    return 0;
}
